#ifndef FILES_H
#define FILES_H

// 		This header contains functions, that nedeed to work with files:
//		write data on file or read data from file

void bzero(void *s, size_t n);

char *read_text_from_file(char *FILENAME); //function reads from text file with name FILENAME all data and returns it

int write_file(char msg[2048], char filename[128]); //this function write msg in file named filename

#endif
