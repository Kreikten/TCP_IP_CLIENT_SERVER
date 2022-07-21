#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#include "BIN/error_proc.h"
#include "BIN/files.h"

int main()
{
   char filename[128];
   char filetext[2048];
   bzero(filename, 128);
   bzero(filetext, 256);
   printf("Enter filename to send: ");
   scanf("%s", filename);
   strcpy(filetext, read_text_from_file(filename));
   int fd = Socket(AF_INET, SOCK_STREAM, 0);
   struct sockaddr_in adr = {0};
   adr.sin_family = AF_INET;
   adr.sin_port = htons(11110);
   Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
   Connect(fd, (struct sockaddr *)&adr, sizeof adr);
   write(fd, filename, sizeof filename);
   sleep(1);
   write(fd, filetext, sizeof filetext);
   close(fd);
   return 0;
}
