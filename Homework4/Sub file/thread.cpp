#include "thread.h"
#include <iostream>
#include <functional>
#include <cstring>
#include<stdio.h>
#include <ThreadClass.h> 
using namespace std;
/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 4                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is the threads for simulation              */
/* -----------------------------------------------------------*/
/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of students                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
void student::ThreadFunc()
{
	Thread::ThreadFunc(); // required
	while (1) {
		Delay();                 // study for a while
		GoToParty();          // go to the party
		Delay();    
	}
	Exit();
}/* ----------------------------------------------------------- */
/* FUNCTION  student                                            */
/*     This method is used for comparison                      */
/* PARAMETER USAGE :                                           */
/*     num: input for the threads current number               */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */student::student(int num) {	this->myNum = num;	this->inParty = false;	muxStd->Lock();
		cout << "Student " << myNum << "starts" << endl;	muxStd->Unlock();}/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of teacher                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */void teacher::ThreadFunc()
{
	Thread::ThreadFunc(); // required
	int i;
	for (i = 0; i < this->m; i++) {     // m is an input value
		Delay();                 // take some rest
		CheckRoom(m,i);          // check the social room
		Delay();                 // take some rest
	}
	muxStd->Lock();
		cout << "teacher lockes the door" << endl;
	Exit();
}

/*---------------------------------------------------------- - */
/* FUNCTION  teacher                                           */
/*     This method is used to set up teacher                   */
/* PARAMETER USAGE :                                           */
/*     M: total number of checks
       max: totla number of students allowed in the party      */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
teacher::teacher(int M, int max) {
	maxCount = max;
	this->m = M;
}