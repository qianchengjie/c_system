#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>

#include<stdlib.h>
#include<unistd.h>
#define FIFO_NAME "/tmp/myfifo"
//有名管道通信
int main(){
	int fd;
	char w_buf[50];
	int w_num;
	if((mkfifo(FIFO_NAME,0777)<0)&&(errno!=EEXIST)){
		printf("cannot create fifo...\n");
		exit(1);
	}
	fd=open(FIFO_NAME,O_WRONLY,0);
	if(fd==-1)
		if(errno==ENXIO){
			printf("cannot open fifo for write...\n");
			exit(1);
		}
		while(1){
			printf("please input something:");
			scanf("%s",w_buf);
			w_num=write(fd,w_buf,strlen(w_buf));
			printf("real write num is %d\n",w_num);
			if(strcmp(w_buf,"exit")==0){break;}
		}
	

	return 0;
}
