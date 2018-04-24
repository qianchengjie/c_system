#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#define BUFNUM 60
//第一题
int main(){
	int n=0;
	pid_t pid;
	int fd[2];
	char buf[BUFNUM];
	pipe(fd);
	if(pid=fork()){
		wait(NULL);
	}else{
		while(pid=fork()){
			n++;
			close(fd[0]);
			scanf("%s",buf);
			write(fd[1],buf,BUFNUM);
			//printf("parentpid:%d\n",pid);
			wait(NULL);
		}
		
		if(!pid&&n>=1){
			close(fd[1]);
			read(fd[0],buf,BUFNUM);
			close(fd[0]);
			write(fd[1],"",BUFNUM);
			if(strcmp("",buf)==0){
				exit(0);
			}
			printf("son read%d: %s\n",pid,buf);
			exit(0);
		}else
			exit(0);
	}

	return 0;
}
