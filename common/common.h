#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
 #include <sys/types.h>
#include <poll.h>
#include <fcntl.h>

#define    SERV_PORT      43211
#define    MAXLINE        4096
#define    LISTENQ        1024





typedef struct { 
    u_int32_t type; 
    char data[1024];
} messageObject;
#define MSG_PING 1
#define MSG_PONG 2
#define MSG_TYPE1 11
#define MSG_TYPE2 21