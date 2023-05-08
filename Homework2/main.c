#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 2/19/2021                                       */
/* PROGRAM ASSIGNMENT # 2                                     */
/* FILE NAME : main										      */
/* PROGRAM PURPOSE :                                          */
/*    This program has 2 main functons that run concurrentlly.*/
/*Function 1 is a quick sort                                  */
/*fuction 2 is mearge for sorted arrays                       */
/* -----------------------------------------------------------*/


/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used to make 2 child prosses to run      */
/* PARAMETER USAGE :                                           */
/*  input file to take in from stdin                           */
/* FUNCTION CALLED :                                           */
/*    none											           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
	int k;//size of array a
	scanf("%d", &k);
	//set up for the frist shared memory for array a
	int i;
	int ShmID;
	int* a;
	key_t key = ftok("./", 'k');
	printf("*** MAIN: shared memory key = %d\n", key);
	ShmID = shmget(key, k * sizeof(int),0666 | IPC_CREAT);
	printf("*** MAIN: shared memory created\n");
	if ((a = (int*) shmat(ShmID, NULL, 0)) < 0)
	{
		perror("shmat");
		_Exit(1);
	}
	printf("*** MAIN: shared memory attached and is ready to use\n\n");
	//inputs for the array a
	printf("Input array for qsort has %d elements:\n  ", k);
	for (i = 0; i < k; i++) {
		scanf("%d", &a[i]);
		printf("  %d", a[i]);
	}
	printf("\n\n");
	//size of array x
	int m;
	scanf("%d", &m);
	//set up second shared momory for array x
	int ShmID2;
	int* x;
	key_t key2 = ftok("./", 'x');
	printf("*** MAIN: shared memory key = %d\n", key2);
	ShmID2 = shmget(key2, m * sizeof(int), 0666 | IPC_CREAT);
	printf("*** MAIN: shared memory created\n");
	if ((x = (int*)shmat(ShmID2, NULL, 0)) < 0)
	{
		perror("shmat");
		_Exit(1);
	}
	printf("*** MAIN: shared memory attached and is ready to use\n\n");
	//inputs for array x
	printf("Input array x[] for merge has %d elements:\n  ", m);
	for (i = 0; i < m; i++) {
		scanf("%d", &x[i]);
		printf("  %d", x[i]);
	}

	printf("\n\n");
	//size of array y
	int n;
	scanf("%d", &n);
	//set up thrid shared momory for array y 
	int ShmID3;
	int* y;
	key_t key3 = ftok("./", 'y');
	printf("*** MAIN: shared memory key = %d\n", key3);
	ShmID3 = shmget(key3, n * sizeof(int), 0666 | IPC_CREAT);
	printf("*** MAIN: shared memory created\n");
	if ((y = (int*)shmat(ShmID3, NULL, 0)) < 0)
	{
		perror("shmat");
		_Exit(1);
	}
	printf("*** MAIN: shared memory attached and is ready to use\n\n");
	//inputs for array y
	printf("Input array y[] for merge has %d elements:\n  ", n);
	for (i = 0; i < n; i++) {
		scanf("%d", &y[i]);
		printf("  %d", y[i]);
	}

	printf("\n\n");
	//size for the out array
	int outLe = m + n;
	//Sets up the fourth and last shared memory for array out
	int ShmID4;
	int* out;
	key_t key4 = ftok("./", 'o');
	printf("*** MAIN: shared memory key = %d\n", key4);
	ShmID4 = shmget(key4, outLe * sizeof(int), 0666 | IPC_CREAT);
	printf("*** MAIN: shared memory created\n");
	if ((out = (int*)shmat(ShmID4, NULL, 0)) < 0)
	{
		perror("shmat");
		_Exit(1);
	}
	printf("*** MAIN: shared memory attached and is ready to use\n\n");
	//spawns the frist process qsort
	printf("*** MAIN: about to spawn the process for qsort\n");
	pid_t pid;
	if ((pid = fork()) < 0) { // fork a child process
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) { // for the child process:
		char* argv[4];
		char left[11];
		char right[11];
		//inputs for argv
		argv[0] = "qsort";
		sprintf(left, "%d", 0);
		argv[1] = left;
		sprintf(right, "%d", k-1);
		argv[2] = right;
		argv[3] = NULL;
		if (execvp("./qsort", argv) < 0) { // execute the command
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	//spawns the second process merge
	char buf[100];
	sprintf(buf, "*** MAIN: about to spawn the process for merge\n");
	write(1, buf, strlen(buf));
	pid_t pid2;
	if ((pid2 = fork()) < 0) { // fork a child process
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid2 == 0) { // for the child process:
		char* argv[4];
		char mLE[11];
		char nLE[11];
		//inputs for argv
		argv[0] = "merge";
		sprintf(mLE, "%d", m);
		argv[1] = mLE;
		sprintf(nLE, "%d", n);
		argv[2] = nLE;
		argv[3] = NULL;
		if (execvp("./merge", argv) < 0) { // execute the command
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	//waits for both children to be finished
	while (wait(NULL) > 0);
	//prints out the sorted array from the quick sort
	printf("*** MAIN: sorted array by qsort:\n   ");
	for (i = 0; i < k; i++) {
		printf("  %d", a[i]);
	}
	printf("\n\n");
	//prints out the finale array from the merged arrays
	printf("*** MAIN: merged array:\n   ");
	for (i = 0; i < outLe; i++) {
		printf("  %d", out[i]);
	}
	printf("\n\n");
	//detaches the shared memory
	shmdt((void*)x);
	shmdt((void*)y);
	shmdt((void*)a);
	shmdt((void*)out);
	printf("*** MAIN: shared memory successfully detached\n");
	printf("*** MAIN: shared memory successfully detached\n");
	printf("*** MAIN: shared memory successfully detached\n");
	printf("*** MAIN: shared memory successfully detached\n");
	//kills the shared memory
	shmctl(ShmID, IPC_RMID, NULL);
	shmctl(ShmID2, IPC_RMID, NULL);
	shmctl(ShmID3, IPC_RMID, NULL);
	shmctl(ShmID4, IPC_RMID, NULL);
	printf("*** MAIN: shared memory successfully removed\n");
	printf("*** MAIN: shared memory successfully removed\n");
	printf("*** MAIN: shared memory successfully removed\n");
	printf("*** MAIN: shared memory successfully removed\n");
	return 0;//ends program
}