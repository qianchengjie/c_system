#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<unistd.h>

#define FIFO_NAME "/tmp/myfifo"
//有名管道通信
int main(){
	char r_buf[50];
	int fd;
	int r_num;
	if((mkfifo(FIFO_NAME,0777)<0)&&(errno!=EEXIST)){
		printf("cannot creat fifo...\n");
		exit(1);
	}	

	fd=open(FIFO_NAME,O_RDONLY,0);
	if(fd==-1){
		printf("cannot open fifo");
		exit(1);
	}

	while(1){
		memset(r_buf,0,sizeof(r_buf));
		r_num=read(fd,r_buf,50);
		if(r_num==-1){
			if(errno==EAGAIN)
				printf("no data avalible\n");
		}
		printf("%d bytes read:%s\n",r_num,r_buf);
		sleep(1);
	}
//	unlink(FIFO_NAME);
	return 0;
}
