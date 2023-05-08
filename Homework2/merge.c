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
/* ----------------------------------------------------------- */
/* NAME : Michael Romero                     User ID: maromero */
/* DUE DATE : 2/10/2021                                        */
/* PROGRAM ASSIGNMENT # 2                                      */
/* FILE NAME : merge										   */
/* PROGRAM PURPOSE :                                           */
/*   This program is used to merge to arrays                   */
/* ----------------------------------------------------------- */


/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used to merge to arrays                  */
/* PARAMETER USAGE :                                           */
/*    m- size of array x
      n- size of array y                                       */
/* FUNCTION CALLED :                                           */
/*    none											           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
	//handles inputs
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int outLe = m + n;

	//sets up shared memory
	key_t key = ftok("./", 'x');
	int kshmID = shmget(key, n * sizeof(int), 0666);
	int* x = (int*)shmat(kshmID, NULL, 0);

	key_t key2 = ftok("./", 'y');
	int kshmID2 = shmget(key2, n * sizeof(int), 0666);
	int* y = (int*)shmat(kshmID2, NULL, 0);

	key_t key3 = ftok("./", 'o');
	int kshmID3 = shmget(key3, outLe * sizeof(int), 0666);
	int* out = (int*)shmat(kshmID3, NULL, 0);

	int i;
	//makes m amount of children
	char buf[120];
	for (i = 0; i < m; i++) {
		pid_t pid;
		if ((pid = fork()) < 0) { // fork a child process
			printf("*** ERROR: forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) {
			sprintf(buf, "      $$$ M-PROC(%d): handling x[%d] = %d\n          ..........\n", 
				getpid(), i, x[i]);
			write(1, buf, strlen(buf));
			if (x[i] < y[0]) {//x[i] is less than all in y
				out[i] = x[i];
				sprintf(buf, "      $$$ M-PROC(%d): x[%d] = %d is found to be smaller than y[%d] = %d\n          ..........\n",
					getpid(), i, x[i], 0, y[0] );
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write x[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, x[i], i);
				write(1, buf, strlen(buf));
			}
			else if(x[i] > y[n-1]) //x[i] is larger of all of y
			{
				out[i + n] = x[i];

				sprintf(buf, "      $$$ M-PROC(%d): x[%d] = %d is found to be larger than y[%d] = %d\n          ..........\n",
					getpid(), i, x[i], (n-1), y[n-1]);
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write x[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, x[i], i + n);
				write(1, buf, strlen(buf));
			}
			else {//y[k] < x[i] < y[n-1]
				int find = binarySearch(y, 0, n, x[i]);
				int index = i + find;

				out[index] = x[i];

				sprintf(buf, "      $$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n          ..........\n",
					getpid(), i, x[i], find - 1, y[find - 1], n-1, y[n-1]);
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write x[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, x[i], index);
				write(1, buf, strlen(buf));
			}
			exit(1);
		}
	}
	//makes n amount of children 
	for (i = 0; i < n; i++) {
		pid_t pid;
		if ((pid = fork()) < 0) { // fork a child process
			printf("*** ERROR: forking child process failed\n");
			exit(1);
		}
		else if (pid == 0) {
			sprintf(buf, "      $$$ M-PROC(%d): handling y[%d] = %d\n          ..........\n",
				getpid(), i, y[i]);
			write(1, buf, strlen(buf));
			if (y[i] < x[0]) {//y[i] < all of x 
				out[i] = y[i];
				sprintf(buf, "      $$$ M-PROC(%d): y[%d] = %d is found to be smaller than x[%d] = %d\n          ..........\n",
					getpid(), i, y[i], 0, x[0]);
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write y[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, y[i], i);
				write(1, buf, strlen(buf));
			}
			else if (y[i] > x[m - 1])//y[i] > all of x
			{
				out[i + m] = y[i];//x[k] < y[i] < x[m-1]

				sprintf(buf, "      $$$ M-PROC(%d): y[%d] = %d is found to be larger than x[%d] = %d\n          ..........\n",
					getpid(), i, y[i], (m - 1), x[m - 1]);
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write y[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, y[i], i + m);
				write(1, buf, strlen(buf));
			}
			else {
				int find = binarySearch(x, 0, m, y[i]);
				int index = i + find;

				out[index] = y[i];

				sprintf(buf, "      $$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n          ..........\n",
					getpid(), i, y[i], find - 1, x[find - 1], m - 1, x[m - 1]);
				write(1, buf, strlen(buf));

				sprintf(buf, "      $$$ M-PROC(%d): about to write x[%d] = %d into position %d of the output array\n          ..........\n",
					getpid(), i, y[i], index);
				write(1, buf, strlen(buf));
			}
			exit(1);
		}
	}

	
	while (wait(NULL) > 0);//waits for all children 
	//detaches all shared memory
	shmdt((void*)x);
	shmdt((void*)y);
	shmdt((void*)out);
	return 0;
}


/* ----------------------------------------------------------- */
/* FUNCTION  binarySearch                                      */
/*     This method is used to find the index location          */
/* PARAMETER USAGE :                                           */
/*    a- array to search throught
	  low- lowest index to search throught                   
	  hight- highest index of the array
	  m- the value to check for the position                   */
/* FUNCTION CALLED :                                           */
/*    main											           */
/* ----------------------------------------------------------- */
int binarySearch(int a[], int low, int high, int m) {
	int i;
	int index;
	for (i = low; i < (high - 1); i++)
	{
		if ((m > a[i]) && (m < a[high-1])) {//find the index of a[i] < m < a[high -1]
			 index = i+1;
		}
	}
	return index;
}
