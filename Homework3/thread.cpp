#include "thread.h"
#include <iostream>
#include <functional>
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 3                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is the threads for comparison              */
/* -----------------------------------------------------------*/

/* ----------------------------------------------------------- */
/* FUNCTION  thread                                            */
/*    thread setup                                             */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    none 											           */
/* ----------------------------------------------------------- */
void thread::ThreadFunc()
{
	Thread::ThreadFunc(); // required
}/* ----------------------------------------------------------- */
/* FUNCTION  sort                                              */
/*     This method is used for comparison                      */
/* PARAMETER USAGE :                                           */
/*     x: pointer to an array
	   n: the position of the element to be checked            */
/* FUNCTION CALLED :                                           */
/*    thread-main.sort 										   */
/* ----------------------------------------------------------- */int thread::sort(int* x, int n) {
	cout << "        Thread " << n << " Created" << endl;
	int temp;
	int Swapped = false;
	cout << "        Thread " << n << " compares x[" << n << "-1] and x[" << n << "]" << endl;
	if (x[n - 1] > x[n]) {
		cout << "        Thread " << n << " swaps x[" << n << "-1] and x[" << n << "]" << endl;
		temp = x[n - 1];
		x[n - 1] = x[n];
		x[n] = temp;
		Swapped = true;
	}
	cout << "        Thread " << n << " exits" << endl;
	return Swapped;
	Exit();}