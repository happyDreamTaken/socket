#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
extern read_data(int sockfd);

int main(int argc,char **argv){
    int listenfd,connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(12345);

    bind(listenfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
    listen(listenfd,1024);
    for(;;){
        clilen=sizeof(cliaddr);
        connfd=accept(listenfd,(struct sockaddr *) &cliaddr,&clilen);
        read_data(connfd);
        close(connfd);
    }
}