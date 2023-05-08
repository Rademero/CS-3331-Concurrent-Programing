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
/* FILE NAME : qsort										  */
/* PROGRAM PURPOSE :                                          */
/*  This program sorts an array using concurrent quick sort   */
/* -----------------------------------------------------------*/

/* ----------------------------------------------------------- */
/* FUNCTION  swap                                              */
/*     This method is used to swap the values passed in        */
/* PARAMETER USAGE :                                           */
/*  a- pointer to a value to be swaped with b                  */
/*  b- pointer to a value to be swaped with a                  */
/* FUNCTION CALLED :                                           */
/*    partition										           */
/* ----------------------------------------------------------- */
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

   /* ----------------------------------------------------------- */
   /* FUNCTION  partition                                         */
   /* This function takes last element as pivot, places
      the pivot element at its correct position in sorted
      array, and places all smaller (smaller than pivot)
      to left of pivot and all greater elements to right
      of pivot                                                    */
   /* PARAMETER USAGE :                                           */
   /*  arr- this is the array to be sorted                        */
   /*  left- the left side of the parition                        */
   /*  right- the right side of the parition                      */
   /* FUNCTION CALLED :                                           */
   /*    quicksort        									      */
   /* ----------------------------------------------------------- */
int partition(int arr[], int left, int right)
{
    printf("\n");
    int pivot = arr[right];    // pivot 
    int i = (left - 1);  // Index of smaller element 
    int j;
    for (j = left; j <= right; j++)
    {
        // If current element is smaller than the pivot 
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return (i + 1);
}

/* ----------------------------------------------------------- */
/* FUNCTION  quicksort                                         */
/*     This method is used create children to call parition
       whitch will sort the array                              */
/* PARAMETER USAGE :                                           */
/*  arr- this is the array to be sorted                        */
/*  left- the left side of the parition                        */
/*  right- the right side of the parition                      */
/* FUNCTION CALLED :                                           */
/*    main  										           */
/* ----------------------------------------------------------- */
void quicksort(int arr[], int left, int right) {
    char buf[100];
    if (left < right)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, left, right);
        sprintf(buf, "   ### Q-PROC(%d): pivot element is a[%d] = %d\n",
            getpid() , pi , arr[pi]);
        write(1, buf, strlen(buf));

        int j;
        
        for (j = left; j <= right; j++) {
            if (j == left) {
                sprintf(buf, "     ");
            }
            sprintf(buf, "  %d");
        }
        sprintf(buf, "\n       ..........\n");


        // Separately sort elements before 
        // partition and after partition
        pid_t pid1;
        if ((pid1 = fork()) < 0) { // fork a child process
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }
        else if (pid1 == 0) { // for the child process:
            char* argv[4];
            char lefts[11];
            char rights[11];

            argv[0] = "qsort";
            sprintf(lefts, "%d", left);
            argv[1] = lefts;
            sprintf(rights, "%d", pi - 1);
            argv[2] = rights;
            argv[3] = NULL;

            if (execvp("./qsort", argv) < 0) { // execute the command quickSort(left, partitionPoint - 1);
                printf("*** ERROR: exec failed\n");
                exit(1);
            }
        }

        pid_t pid2;
        if ((pid2 = fork()) < 0) { // fork a child process
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }
        else if (pid2 == 0) { // for the child process:
            char* argv[4];
            char lefts[11];
            char rights[11];

            argv[0] = "qsort";
            sprintf(lefts, "%d", pi + 1);
            argv[1] = lefts;
            sprintf(rights, "%d", right);
            argv[2] = rights;
            argv[3] = NULL;
    
            if (execvp("./qsort", argv) < 0) { // execute the command  quickSort(partitionPoint + 1, right);
                printf("*** ERROR: exec failed\n");
                exit(1);
            }
        }
    }
}

/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used set up the shared memory and 
       detatch it                                              */
/* PARAMETER USAGE :                                           */
/*  left- the left side of the parition                        */
/*  right- the right side of the parition                      */
/* FUNCTION CALLED :                                           */
/*    none  										           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
    //handels inputs
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    char buf[100];
    sprintf(buf, "   ### Q-PROC(%d): entering with a[%d..%d]\n       ..........\n",getpid(),left,right);
    write(1, buf, strlen(buf));
    int n = right - left;

    //sets up shared memory
    key_t key = ftok("./", 'k');
    int kshmID = shmget(key, n * sizeof(int), 0666);
    int* arr = (int*)shmat(kshmID, NULL, 0);
    sprintf(buf, "       ..........\n");
    //starts the sort
    if (left < right) {
        quicksort(arr, left, right);
        while (wait(NULL) > 0);//race condition chatch 
    }
    else {
        while (wait(NULL) > 0);//waits for all processes to end
      }
    
       //detatches the shared momory
    shmdt((void*)arr);
    return 0;
}
