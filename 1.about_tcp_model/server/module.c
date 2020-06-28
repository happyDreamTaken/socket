#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//size_t表示实际有多少数据被拷贝了

size_t readn(int fd,void *buffer,size_t size){
    char *buffer_pointer=buffer;
    int length =size;
    while(length>0){
        int res = read(fd, buffer_pointer,length);
        if(res<0){
            if(errno == EINTR){
                continue;
            }else{
                return (-1);
            }
        }else if(res==0){
            break;
        }
        length-=res;
        buffer_pointer +=res;
    }
    return size-length;
}

void read_data(int sockfd){
    ssize_t n;
    char buf[1024];
    int time=0;

    for(;;){
        fprintf(stdout,"block in read\n");
        if(n=readn(sockfd,buf,1024) ==0){
            return;
        }
        time++;
        fprintf(stdout, "1K read for %d \n", time);
        usleep(1000);
    }
}

