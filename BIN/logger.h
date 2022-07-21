#ifndef LOGGER_H
#define LOGGER_H

//		This headder contains functions, that needed to logging all daemon actions
//		It can get system time and then write in log file time and message that we 
//		want to write

void bzero(void *s, size_t n);
char *getTime();  //function returns current system time in string(char * ) format
int write_log(char msg[256]); //function write in log file(placed in daemon directory) message msg with current time

#endif
