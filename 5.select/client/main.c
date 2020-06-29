#include "../../common/common.h"

int main(int argc,char **argv){
    if(argc!=2){
        error(1,0,"ip!!");
    }
    int socket_fd;
    socket_fd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&server_addr.sin_addr);

    socklen_t server_len=sizeof(server_addr);
    int connect_rt=connect(socket_fd,(struct sockaddr *) &server_addr,server_len);
    if(connect_rt<0){
        error(1,errno,"connect faild");
    }

    char recv[MAXLINE],send_line[MAXLINE+1];
    int n;

    fd_set readmask;
    fd_set allreads;
    FD_ZERO(&allreads);
    FD_SET(0,&allreads);
    FD_SET(socket_fd,&allreads);

    for(;;){
        readmask = allreads;
        int rc=select(socket_fd+1,&readmask,NULL,NULL,NULL);
        if(rc<=0){
            error(1,0,"select faild");
        }

        if(FD_ISSET(socket_fd,&readmask)){
            n=read(socket_fd,recv,MAXLINE);
            if(n<0){
                error(1,errno,"read error");
            }else if(n=0){
                error(1,0,"server terminated\n");
            }
            recv[n]='0';
            printf("hi %s\n",recv);
            exit(0);
        }
        if(FD_ISSET(STDIN_FILENO,&readmask)){
            if(fgets(send_line,MAXLINE,stdin)!=NULL){
                int i=strlen(send_line);
                if(send_line[i-1]=='\n'){
                    send_line[i-1]==0;
                }
                printf("now sending %s\n",send_line);
                size_t rt=write(socket_fd,send_line,strlen(send_line));
                if(rt<0){
                    error(1,errno,"write faild");
                }
                printf("send bytes %zu\n",rt);
            }
        }
    }

    
}