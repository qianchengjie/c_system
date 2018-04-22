#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#define BUFNUM 60
// 无名管道通信
int main(void){
	int n;
	int fd[2];
	pid_t pid;
	char buf[BUFNUM];
	if(pipe(fd)>0){
		fprintf(stderr,"creat pipe Error: %s \n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	if((pid=fork())<0){
		fprintf(stderr,"Fork error: %s \n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(pid>0){
		close(fd[0]);
		write(fd[1],"I'm your father.\n",17);
		write(fd[1],"I'm watier for you .\n",35);
		wait(NULL);
	}
	else{
		close(fd[1]);
		n=read(fd[0],buf,BUFNUM);
		printf("%d btys read:%s",n,buf);
	}
	return 0;
}
