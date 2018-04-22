#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<unistd.h>
#define MSG_FILE "shm_reader.c"
#define SIZE 255
#define PERM S_IRUSR|S_IWUSR

char buf1[SIZE];
//共享内存通信
int main(){
	key_t key;
	int shmid;
	struct shmid_ds buf;
	char *shmaddr1;
	int i;
	if((key=ftok(MSG_FILE,66))==-1){
		fprintf(stderr,"Creat key Error:%s \n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	if((shmid=shmget(key,SIZE,PERM|IPC_CREAT))==-1){
		fprintf(stderr,"Create sharememory Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("reader: shmid=%d\n",shmid);
	if((shmaddr1=(char *)shmat(shmid,NULL,0))==(void *)-1){
		fprintf(stderr,"Attach sharememory Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("reader: shmaddr=%s\n",shmaddr1);
	for(i=0;i<10;i++){
		strncpy(buf1,shmaddr1,SIZE);
		printf("reader %d: %s\n",i,buf1);
	}

	if(shmdt(shmaddr1)==-1){
		fprintf(stderr,"Detach Sharememory Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	sleep(5);
	if(shmctl(shmid,IPC_RMID,&buf)==-1){
		fprintf(stderr,"Remove sharememory erro:%s\n",strerror(errno));
		exit(EXIT_FAILURE);	
	}
	exit(EXIT_SUCCESS);

}
