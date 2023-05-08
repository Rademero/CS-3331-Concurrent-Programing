#include "thread.h"
#include <iostream>
using namespace std;
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 3                                     */
/* FILE NAME : thread-main									  */
/* PROGRAM PURPOSE :                                          */
/*    This program sorts an array by calling threads.         */
/* -----------------------------------------------------------*/
#define Even 0  /* even pass starts from 1+Even */
#define Odd  1  /* odd pass starts from 1+Odd   */

/* ----------------------------------------------------------- */
/* FUNCTION  sort                                              */
/*     This method is used to make a thread for comparison     */
/* PARAMETER USAGE :                                           */
/*  Pass: even or odd
	x[]: the array of ints to be sorted                        */
/* FUNCTION CALLED :                                           */
/*    main 											           */
/* ----------------------------------------------------------- */
int  Sort(int Pass, int x[], int n)
{
	int i, temp, Swapped = true;
	for (i = 1 + Pass; i < n; i += 2) {
		thread* t;
		t = new thread();
		Swapped = t->sort(x, i);
	}
	return Swapped;
}

/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used to sort the array and handle input  */
/* PARAMETER USAGE :                                           */
/*  input file to take in from stdin                           */
/* FUNCTION CALLED :                                           */
/*    none											           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
	cout << "Concurrent Even-Odd Sort" << endl;
	int k;//size of array a
	cin >> k;
	int a[k];
	int j = 0;
	cout << "Number of input data = " << k << endl <<"Input array:" << endl;
	int c = 0;
	for (j = 0; j < k; j++) {
		int temp;
		cin >> temp;
		a[j] = temp;
		cout << "    " << a[j];
		c++;
		if (c >= 20) {
			cout << endl;//check for only 20 a line
		}
	}
	cout << endl;
	//size of array x

	/*This is the even-odd sorting function        */

	int  Swapped,n;
	n = 0;
	Swapped = true;
	while (n < k) {
		Swapped = Sort(Even, a, k);             /* Even Pass  */
		cout << "    Even Pass:" << endl;
		Swapped = Swapped || Sort(Odd, a, k);   /* Odd Pass   */
		cout << "    Odd Pass:" << endl;
		n++;//counter to force only n interations
	}
	c = 0;
	cout << "Final result after iteration " << n << ":" << endl;
	for (j = 0; j < k; j++) {
		cout << "    " << a[j];
		c++;
		if (c >= 20) {
			cout << endl;//check for only 20 a line
		}
	}
	cout << endl;
}

