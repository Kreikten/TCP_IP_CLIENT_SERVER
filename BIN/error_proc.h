#ifndef ERROR_PROC_H
#define ERROR_PROC_H
#include <sys/types.h>
#include <sys/socket.h>


//  This header contains functions, that needed to handle possible errors at different steps
//  of sending data using TCP/IP protocol


int Socket(int domain, int type, int protocol);  //creating socket and write error if it is impossible
void Bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen); //connect socket with protocol and write error if it is impossible

void Listen(int sockfd, int backlog); // inform OS that server listen socket  and write error if it is impossible
int Accept(int sockfd, struct sockaddr * addr, socklen_t *addrlen); //accepting connection to socket and write error if it is impossible

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 

void Inet_pton(int af, const char* src, void *dst); //convert string to network address format, else exit with error

#endif
