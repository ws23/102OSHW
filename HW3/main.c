#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#define NUM_THREADS 5
#define MAX 121021

void *runner(void*);
void showHelp();

FILE *fout;

int main(int arc, char *arv[]){
	int i; 
	char file[100] = {0};

	if(arc==1){
		printf("argument miss!!\n");
		showHelp();
		return 0;
	}

	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr; 

	pthread_attr_init(&attr);

	for(i=1;i<arc;i++){
		if(strcmp(arv[i], "-p")==0)
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
		else if(strcmp(arv[i], "-s")==0)
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
		else if(strcmp(arv[i], "-f")==0)
			pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
		else if(strcmp(arv[i], "-r")==0)
			pthread_attr_setschedpolicy(&attr, SCHED_RR);
		else if(strcmp(arv[i], "-o")==0){
			i++;
			if(i<arc)
				strcpy(file, arv[i]);
			else{
				printf("file name miss!!\n");
				showHelp();
			}

		}
		else
			printf("argument error. (%s)\n", arv[i]);
	}

	if(file[0]!=0)
		fout = fopen(file, "w");
	else
		fout = stdout;

	printf("Thread ID   Turnaround Time\n");
	printf("----------  ---------------\n");

	for(i=0;i<NUM_THREADS;i++)
		pthread_create(&tid[i], &attr, runner, NULL);

	for(i=0;i<NUM_THREADS;i++)
		pthread_join(tid[i], NULL);
	fclose(fout);
	return 0;
}

void *runner(void *param){
	int i,j;
	struct timeval t_e, t_e2;
	struct timezone tz_e;
	pthread_t tid = pthread_self();
	gettimeofday(&t_e, &tz_e);
	for (i=0;i<100;i++){
		for (j=0;j<MAX;j++)
			fprintf(fout, "");
		fprintf(fout, "Tid [%lu][%d]\n",tid,i); 
	}
	gettimeofday(&t_e2, &tz_e);
	printf("%-11lu  %ld us\n", tid, 1000000*(t_e2.tv_sec-t_e.tv_sec)+t_e2.tv_usec-t_e.tv_usec);
	pthread_exit(0);
}

void showHelp(){
	printf("============= HELP ===============\n");
	printf("Process Scope:\n\t ./myscheduler -p\n");
	printf("System Scope:\n\t ./myscheduler -s\n");
	printf("First-Come-First-Serve:\n\t ./myscheduler -f\n");
	printf("Round-Robin:\n\t ./myscheduler -r\n");
	printf("Ouput file:\n\t ./myscheduler -o [filename]\n");
	printf("\t\t\t\t\t\tby 410121021 林育慈\n");
}
