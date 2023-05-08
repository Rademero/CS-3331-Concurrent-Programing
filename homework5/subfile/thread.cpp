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
}/* ----------------------------------------------------------- */
/* FUNCTION  AskQuestion                                       */
/*     This method is for the elfs to ask questions            */
/* PARAMETER USAGE :                                           */
/*     num: input for the threads current number               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-Elf::threadfunc 							   */
/* ----------------------------------------------------------- */void workFlow::AskQuestion(int num) {	MonitorBegin();	if (numOfElfs != 3) {		muxStd->Lock();
			cout << "          Elf " << num << " has a problem" << endl;		muxStd->Unlock();		elfArr[numOfElfs] = num;		numOfElfs++;		if (numOfElfs == 3) {			muxStd->Lock();
				cout << "          Elf " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << " wake up the Santa" << endl;			muxStd->Unlock();			threeElfs = true;			wakeSanta->Signal();			questionAnswered->Wait();			muxStd->Lock();
				cout << "          Elf " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << " return to work" << endl;			muxStd->Unlock();			threeElfs = false;			int i;			for (i = 0; i < 3; i++) {				elfArr[i] = 0;			}			numOfElfs = 0;			lineCleared->Signal();		}		else {			questionAnswered->Wait();		}	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  FlyOff                                            */
/*     This method is for the reindeer to flyoff               */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */void workFlow::FlyOff() {	MonitorBegin();		takeOff->Wait();	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  Sleep                                            */
/*     This method is for the santa to sleep                   */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */void workFlow::Sleep(){	MonitorBegin();		if (!threeElfs && !allRiendeer) {			wakeSanta->Wait();		}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  ReindeerBack                                      */
/*     This method is for the reindeer to comeback             */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer
	   max:how many are left								   */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */void workFlow::ReindeerBack(int num, int max){	MonitorBegin();	numOfReaindeer++;	if (numOfReaindeer == totalReindeer) {		allRiendeer = true;	}	else {		muxStd->Lock();
			cout << "     Reindeer " << num << " returns" << endl;		muxStd->Unlock();	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  WaitOthers                                      */
/*     This method is for the reindeer to wait for the others  */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer                                    */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */void workFlow::WaitOthers(int num){	MonitorBegin();	if (!allRiendeer) {		Gather->Wait();	}	else {		muxStd->Lock();
			cout << "     The last reindeer " << num << " wakes up Santa" << endl;		muxStd->Unlock();		wakeSanta->Signal();		Gather->Wait();	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  WaitSleigh                                        */
/*     This method is for the reindeer to wait for the sleigh  */
/* PARAMETER USAGE :                                           */
/*     num:current reindeer                                    */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-reindeer::threadfunc 						   */
/* ----------------------------------------------------------- */void workFlow::WaitSleigh(){	MonitorBegin();		sleightsReady->Wait();	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  SleighReady                                       */
/*     This method is for the santa to set up the sleigh       */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */void workFlow::SleighReady() {	MonitorBegin();	muxStd->Lock();
	cout << "Santa is preparing sleighs" << endl;	muxStd->Unlock();	int i;	for (i = 0; i < totalReindeer; i++) {		sleightsReady->Signal();	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  workFlow                                          */
/*     This method is to set up the monitor                    */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::santa   						        */
/* ----------------------------------------------------------- */workFlow::workFlow(){	wakeSanta = new Condition("wakeSanta");	questionAnswered = new Condition("questionAnswered");	Gather = new Condition("Gather");	sleightsReady = new Condition("sleightsReady");	takeOff = new Condition("takeOff");	lineCleared = new Condition("lineCleared");	int i = 0;	for (i=0;i<3;i++){		elfArr[i] = 0;	}}/* ----------------------------------------------------------- */
/* FUNCTION  AnswerElfs                                       */
/*     This method is for the santa to answer the elfs        */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */void workFlow::AnswerElfs() {	MonitorBegin();	muxStd->Lock();
		cout << "Santa answers the question posted by elves " << elfArr[0] << ", " << elfArr[1] << ", " << elfArr[2] << endl;	muxStd->Unlock();		questionAnswered->Signal();		questionAnswered->Signal();		questionAnswered->Signal();	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  GatherAll                                       */
/*     This method is for the santa to gather the reindeer     */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */void workFlow::GatherAll() {	MonitorBegin();	int i;	for (i = 0; i < totalReindeer; i++) {		Gather->Signal();	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  Delivered                                       */
/*     This method is for the santa to deliver the presents    */
/* PARAMETER USAGE :                                           */
/*     none										               */
/* FUNCTION CALLED :                                           */
/*    thread.cpp-santa::threadfunc   						   */
/* ----------------------------------------------------------- */void workFlow::Delivered(int num) {	MonitorBegin();	muxStd->Lock();
		cout << "The team flies off ("<< num << ")!" << endl;	muxStd->Unlock();	allRiendeer = false;	numOfReaindeer = 0;	int i;	for (i = 0; i < totalReindeer; i++) {		takeOff->Signal();	}	MonitorEnd();}/* ----------------------------------------------------------- */
/* FUNCTION  Elf                                               */
/*     This method is to set up the elfs                       */
/* PARAMETER USAGE :                                           */
/*     num: input for the threads current number               */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */Elf::Elf(int num) {	myNum = num;	muxStd->Lock();
		cout << "          Elf " << myNum << " starts" << endl;	muxStd->Unlock();}/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of Reindeer                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */void Reindeer::ThreadFunc()
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
				cout << "Santa is helping elves" << endl;			muxStd->Unlock();
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
		cout << "Santa thread starts"<< endl;	muxStd->Unlock();
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
		cout << "     Reindeer " << myNum << " starts" << endl;	muxStd->Unlock();
}