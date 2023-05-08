#include "thread.h"
#include <iostream>
#include <ThreadClass.h> 
using namespace std;
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 5                                     */
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

	int e = atoi(argv[1]);
	int r = atoi(argv[2]);
	int t = atoi(argv[3]);
	if (t == 0) {
		t = 5;
	}
	if (e == 0) {
		e = 7;
	}
	if (r == 0) {
		r = 9;
	}

	Santa* santa;
	santa = new Santa(t,r);
	Elf* elf[e];
	int i = 0;
	for (i = 0; i < e; i++) {
		elf[i] = new Elf(i+1);
		elf[i]->Begin();
	}
	Reindeer* reindeer[r];
	for (i = 0; i < r; i++) {
		reindeer[i] = new Reindeer(i + 1);
		reindeer[i]->Begin();
	}
	santa->Begin();
	santa->Join();
	
	cout << "After ("<< t << ") deliveries, Santa retires and is on vacation!" << endl;
}


