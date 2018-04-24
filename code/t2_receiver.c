#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/msg.h>
#define MSG_FILE "t2.c"
#define BUFNUM 255
#define PERM S_IRUSR|S_IWUSR
//第二题接受数据
struct msgbuf{
	long mtype;
	char mtext[BUFNUM+1];
};
int main(){
	
	struct msgbuf msg;
	key_t key;
	int msgid;
	int i;
	char myask[BUFNUM]="end";
	key=ftok(MSG_FILE,66);
	msgid=msgget(key,PERM|IPC_CREAT);
	while(1){
		msgrcv(msgid,&msg,sizeof(struct msgbuf),-1,0);
		if((strcmp("exit",msg.mtext))==0){
			msg.mtype=2;
			//myask[]="end";
			strncpy(msg.mtext,myask,BUFNUM);
			msgsnd(msgid,&msg,sizeof(struct msgbuf),0);
			printf("reader is over!!!!!!!\n");
			break;
		}	
		printf("reader: %s\n",msg.mtext);
	
		msg.mtype=2;
		strncpy(msg.mtext,"funk you c!!!!!",BUFNUM);
		msgsnd(msgid,&msg,sizeof(struct msgbuf),0);
	}
	return 0;
}
