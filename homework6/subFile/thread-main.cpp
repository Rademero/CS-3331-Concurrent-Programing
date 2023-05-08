#include "thread.h"
#include <iostream>
#include <ThreadClass.h> 
using namespace std;
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 6                                     */
/* FILE NAME : thread-main									  */
/* PROGRAM PURPOSE :                                          */
/*    This program counts all prime numbers between 2 and n   */
/* -----------------------------------------------------------*/
/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used to handel inputs                    */
/* PARAMETER USAGE :                                           */
/*  input file to take in from stdin                           */
/* FUNCTION CALLED :                                           */
/*    none											           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
	int n;

	if (argc <= 1) {
		n = 30;
	}
	else {
		n = atoi(argv[1]);
	}
	

	Master* master;
	master = new Master(n);
	master->Begin();
	
	master->Join();
}


