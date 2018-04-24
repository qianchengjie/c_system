#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#define MSG_FILE "t2.c"
#define BUFNUM 255
#define PERM S_IRUSR|S_IWUSR
//第二题
struct msgbuf{
	long mtype;
	char mtext[BUFNUM+1];
};
char message[BUFNUM];
int main(){
	struct msgbuf msg;
	key_t key;
	int msgid;
	int i;
	key=ftok(MSG_FILE,66);
	while(1){
		msgrcv(msgid,&msg,sizeof(struct msgbuf),2,0);
		if((strcmp(msg.mtext,"end"))==0){
			printf("writer is over!!!!!!!!\n");
			exit(0);
		}
		scanf("%s",message);
		msgid=msgget(key,PERM|IPC_CREAT);
		msg.mtype=1;
//		msg.mtext=message[0];
		strncpy(msg.mtext,message,BUFNUM);
//		msg.mtext=message;
		msgsnd(msgid,&msg,sizeof(struct msgbuf),0);
		memset(&msg,'\0',sizeof(struct msgbuf));
	
	
		//msgrcv(msgid,&msg,sizeof(struct msgbuf),2,0);
		//printf("rcv:%s\n",msg.mtext);
	}
	msgctl(msgid,IPC_RMID,0);
	return 0;
}
