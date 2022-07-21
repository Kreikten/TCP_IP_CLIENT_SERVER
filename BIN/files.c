#include <stdio.h>
#include <string.h>
#include "files.h"
//#include "logger.h"
char *read_text_from_file(char *FILENAME)
{
    static char buf[2048] = "";
    FILE *file;
    int flag_first = 1;

    file = fopen(FILENAME, "r");
    printf("POINTER = %p\n", file);

    if (file != NULL)
    {
       /* char temp[256];
        while (fscanf(file, "%s", temp) != EOF)
        {
            printf("\n NEW STROKE  - %s\n", temp);
            if (flag_first)
            {
                strcpy(buf, temp);
               // strcat(buf, "\n");
                flag_first = 0;
            }
            else
            {
                strcat(buf, temp);
                //strcat(buf, "\n");
            }
        }*/

         char temp[1000];
        fgets(temp,1000,file);
        do 
        {
         //   int i = fscanf(file, "%s\n", temp);
            
            if (flag_first)
            {
                strcpy(buf, temp);
               // strcat(buf, "\n");
                flag_first = 0;
            }
            else
            {
                strcat(buf, temp);
                //strcat(buf, "\n");
            }
         //   printf("\n NEW STROKE  - %s\n", temp);
        }while (fgets(temp,1000,file));
    }

    printf("TEXT = %s\n", buf);
    printf("FILENAME = %s\n", FILENAME);
    fclose(file);
    return buf;
}

int write_file(char msg[2048], char filename[128])
{ 

    FILE *pLog;
    char buf[256] = "server_";
    strcat(buf,filename);
    pLog = fopen(buf, "w+");
    //write_log("file opened to write");
    if (pLog == NULL)
    {
      // write_log("file opened to write");
        return 1;
    }

    char str[312];
    bzero(str, 312);

    strcpy(str, msg);
    fputs(str, pLog);

    fclose(pLog);

    return 0;
}
