#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <syslog.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>

#include "BIN/error_proc.h"
#include "BIN/files.h"
#include "BIN/logger.h"

int Daemon(void);
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);

enum SERVER_STATES

//
//          this enum created for creating simple finite state machine:
//          receiving successively from user filename, file data and EOF
{
    GET_FILE_NAME = 0,
    GET_FILE_TEXT = 1,
    GET_END_OF_TRANSMISSION_SIGNAL = 2
};

int main()
{
    char* temp;
    write_log("Daemon Start");

    pid_t parpid, sid;

    parpid = fork(); //creating another instance
    if (parpid < 0)
    {
        exit(1);
    }
    else if (parpid != 0)
    {
        exit(0);
    }
    umask(0);       //giving us permission to work with filesystem
    sid = setsid(); //generate unique instance num
    write_log("sid_generated");
    if (sid < 0)
    {
        exit(1);
    }
    //  if((chdir("/")) < 0) {//выходим в корень фс
    //     write_log("chdir<0");
    //     exit(1);
    //}
    close(STDIN_FILENO); //closing I/O default streamms
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    return Daemon();
}

int Daemon(void)   // endless daemon cycle function
{ 
    int state;
    write_log("START DAEMON");
    while (1)
    {
        char filename[128];
        char filetext[2048];
        bzero(filename, 128);
        bzero(filetext, 2048);

        int server = Socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in adr = {0};
        adr.sin_family = AF_INET;
        adr.sin_port = htons(11110);
        Bind(server, (struct sockaddr *)&adr, sizeof adr);
        Listen(server, 5);
        socklen_t adrlen = sizeof adr;
        int fd = Accept(server, (struct sockaddr *)&adr, &adrlen);

        state = 0;  //we need every time before loop set state at 0
        while (1)
        {

            ssize_t nread;
            char buf[2048];
            nread = read(fd, buf, 2048); //read user message
            if (nread == -1)
            {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            
            switch (state)
            {
            case GET_FILE_NAME: //if current state is 0 this means we received filename
                state = 1;
                
                strcpy(filename, buf);
                write_log(filename);
                break;

            case GET_FILE_TEXT: //if current state is 1 this means we received file data
                state = 2;
                strcpy(filetext, buf);
                break;
            case GET_END_OF_TRANSMISSION_SIGNAL:   //if current state is 2 this means we received end of transmission, set state to 0
                state = 0;
                break;
            }
            if (nread == 0)
            {

                write_log("EOF reached");
                break;
            }
        }
        write_log("END_DAEMON");
        int flag = write_file(filetext, filename); //write results on file
        write_log("end writing resulting file");
        sleep(5);   //set 5 seconds delay
        close(fd);
        close(server);
    }
    return 0;
}