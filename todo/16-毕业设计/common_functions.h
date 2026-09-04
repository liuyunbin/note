



#ifndef WRAPPER_FUNCTION_H
#define WRAPPER_FUNCTION_H 1


#include<arpa/inet.h>
#include<assert.h>
#include<ctype.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<grp.h>
#include<netdb.h>
#include<netinet/tcp.h>
#include<pwd.h>
#include<signal.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>
#include<unistd.h>

#define MAX_SIZE 1024

int Accept(int, void*, socklen_t* );

int Bind(int, const struct sockaddr*, socklen_t); 

int Connect(int, const struct sockaddr*, socklen_t );

void error_exit( int, const char* );

char* Fgets( char*, int, FILE* );

int Inet_pton( int, const char* , void* );

int Listen( int, int );

int Read( int, void*, size_t );

int Socket(int, int, int);

int Write( int, const char* );

#endif
