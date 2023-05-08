#include "thread.h"
#include <iostream>
#include <functional>
#include <cstring>
#include<stdio.h>
#include <ThreadClass.h> 
using namespace std;

static int numOfElfs = 0;
static bool threeElfs = false;
static bool allRiendeer = false;
static int numOfReaindeer;
static workFlow* WorkFlow;
static int totalReindeer;

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 5                                     */
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
void Elf::ThreadFunc()
{
	Thread::ThreadFunc(); // required
	while (1) {
		Delay();                 // make toys
		WorkFlow->AskQuestion(myNum);        // encounter a problem
		Delay();                 // problem solved, take a rest
	}
	Exit();
}
/* FUNCTION  AskQuestion                                       */
/*     This method is for the elfs to ask questions            */
/* PARAMETER USAGE :                                           */
/*     num: input for the threads current number               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-Elf::threadfunc 							   */
/* ----------------------------------------------------------- */
			cout << "          Elf " << num << " has a problem" << endl;
				cout << "          Elf " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << " wake up the Santa" << endl;
				cout << "          Elf " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << " return to work" << endl;
/* FUNCTION  FlyOff                                            */
/*     This method is for the reindeer to flyoff               */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */
/* FUNCTION  Sleep                                            */
/*     This method is for the santa to sleep                   */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */
/* FUNCTION  ReindeerBack                                      */
/*     This method is for the reindeer to comeback             */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer
	   max:how many are left								   */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */
			cout << "     Reindeer " << num << " returns" << endl;
/* FUNCTION  WaitOthers                                      */
/*     This method is for the reindeer to wait for the others  */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer                                    */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */
			cout << "     The last reindeer " << num << " wakes up Santa" << endl;
/* FUNCTION  WaitSleigh                                        */
/*     This method is for the reindeer to wait for the sleigh  */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer                                    */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */
/* FUNCTION  SleighReady                                       */
/*     This method is for the santa to set up the sleigh       */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */
	cout << "Santa is preparing sleighs" << endl;
/* FUNCTION  workFlow                                          */
/*     This method is to set up the monitor                    */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::santa   						        */
/* ----------------------------------------------------------- */
/* FUNCTION  AnswerElfs                                       */
/*     This method is for the santa to answer the elfs        */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */
		cout << "Santa answers the question posted by elves " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << endl;
/* FUNCTION  GatherAll                                       */
/*     This method is for the santa to gather the reindeer     */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */
/* FUNCTION  Delivered                                       */
/*     This method is for the santa to deliver the presents    */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */
		cout << "The team flies off ("<< num << ")!" << endl;
/* FUNCTION  Elf                                               */
/*     This method is to set up the elfs                       */
/* PARAMETER USAGE :                                           */
/*     num: input for the threads current number               */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
		cout << "          Elf " << myNum << " starts" << endl;
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of Reindeer                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
{
	Thread::ThreadFunc(); // required
	while (1) {
		Delay();                 // tan on the beaches
		WorkFlow->ReindeerBack(myNum,totalReindeer);       // report back to Santa
		WorkFlow->WaitOthers(myNum);         // wait for others
								 // Don't forget: the last wakes up Santa
		WorkFlow->WaitSleigh();          // wait for attaching sleigh
		WorkFlow->FlyOff();             // fly off to deliver toys
									 // Santa will let go all reindeers
		Delay();                 // prepare for vacation
	}
	Exit();
}
/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of Santa                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
void Santa::ThreadFunc() 
{
	Thread::ThreadFunc();
	int toysDeliver = 0;
	while (toyCount > toysDeliver) {
			WorkFlow->Sleep();
			if (allRiendeer) { // delivery has a higher priority
				Delay();
				WorkFlow->GatherAll();// gather all reindeers
				Delay();
				WorkFlow->SleighReady();// put on sleigh
				 // and fly off
				Delay();            // Santa delivers toys
				// release all reindeer for vacation
				toysDeliver++;
				WorkFlow->Delivered(toysDeliver);
			}
		if (threeElfs) { // there many be a # of groups waiting
			 // let elves in
			muxStd->Lock();
				cout << "Santa is helping elves" << endl;
			Delay();            // solve their problem
			WorkFlow->AnswerElfs();
			// solve the problem and release elves
		}
	}
	Exit();
}
/* ----------------------------------------------------------- */
/* FUNCTION  Santa                                               */
/*     This method is to set up the Santa                       */
/* PARAMETER USAGE :                                           */
/*     num: input for number or iterations      
       max: total number of reindeer                           */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
Santa::Santa(int num, int max) {
	toyCount = num;
	muxStd->Lock();
		cout << "Santa thread starts"<< endl;
	WorkFlow = new workFlow();
	numOfReaindeer = 0;
	totalReindeer = max;
}

/*---------------------------------------------------------- - */
/* FUNCTION  Reindeer                                           */
/*     This method is used to set up Reindeer                   */
/* PARAMETER USAGE :                                           */
/*     num:what reandeer it is                                 */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
Reindeer::Reindeer(int num) {
	myNum = num;
	muxStd->Lock();
		cout << "     Reindeer " << myNum << " starts" << endl;
}