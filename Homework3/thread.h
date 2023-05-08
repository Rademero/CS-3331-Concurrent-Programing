#include <ThreadClass.h>

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 3                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is a header file to be used for later      */
/* -----------------------------------------------------------*/
class thread : public Thread 
{
public:
	int sort(int x[], int n);
private:
	void ThreadFunc();
};
