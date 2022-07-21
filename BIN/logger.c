#include <time.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"

char *getTime()
{
    time_t now;
    struct tm *ptr;
    static char tbuf[64];
    bzero(tbuf, 64);
    time(&now);
    ptr = localtime(&now);
    strftime(tbuf, 64, "%Y-%m-%e %H:%M:%S", ptr);

    return tbuf;
}

int write_log(char msg[256])
{ 
    FILE *pLog;
    pLog = fopen("log.txt", "a+");

    if (pLog == NULL)
    {
        return 1;
    }
    char str[312];

    bzero(str, 312);

    strcpy(str, getTime());
    strcat(str, " ==========================\n");
    strcat(str, msg);
    strcat(str, "\n");

    fputs(str, pLog);

    fclose(pLog);
    return 0;
}
