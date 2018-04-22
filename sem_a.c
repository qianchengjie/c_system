#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<semaphore.h>
#include<errno.h>

#define PERM S_IRUSR|S_IWUSR

int  main(){
	sem_t *sem;
	if((sem=sem_open("/mysemaphore",O_CREAT,PERM,0))==SEM_FAILED){
		fprintf(stderr,"Creat Semaphore Error:%s \n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("This is A process,i'm wait for B...\n");
	if(sem_wait(sem)==-1){
		fprintf(stderr,"Wait operation Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(sem_wait(sem)==-1){
		fprintf(stderr,"wait operation Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("A process after waiting.\n");
	sem_close(sem);
	if(sem_unlink("/mysemaphore")==-1){
		fprintf(stderr,"Remove semaphore Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	return 0;
}
