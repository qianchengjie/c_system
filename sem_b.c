#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<semaphore.h>
#include<errno.h>
#include<unistd.h>
#define PERM S_IRUSR|S_IWUSR

int main(){
	sem_t *sem;
	if((sem=sem_open("/mysemaphore",O_CREAT,PERM,0))==SEM_FAILED){
		fprintf(stderr,"Creat Semaphore Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("This is B poress ,I'm waiter By .....\n");
	sleep(5);
	if(sem_post(sem)==-1){
		fprintf(stderr,"Waiter operation Error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("This is B proess : A can go now ~\n");
	sem_close(sem);

	return 0;
}
