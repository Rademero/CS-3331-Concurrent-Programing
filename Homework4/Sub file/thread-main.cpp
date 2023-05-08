#include "thread.h"
#include <iostream>
#include <ThreadClass.h> 
using namespace std;
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 4                                     */
/* FILE NAME : thread-main									  */
/* PROGRAM PURPOSE :                                          */
/*    This program run a simulation                 .         */
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

	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int k = atoi(argv[3]);
	if (m == 0) {
		m = 5;
	}
	if (n == 0) {
		n = 5;
	}
	if (k == 0) {
		k = 10;
	}

	teacher* teach;
	teach = new teacher(m, n);
	student* students[k];
	int i = 0;
	for (i = 0; i < k; i++) {
		students[i] = new student(i+1);
		students[i]->Begin();
	}
	teach->Begin();
	teach->Join();
	
	cout << "The landlord finishes checking and forces everyone to leave" << endl;
}


