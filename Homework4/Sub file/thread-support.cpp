#include <iostream>
#include <functional>
#include <cstring>
#include<stdio.h>
#include "thread.h"
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

static int numInRoom = 0;
static Mutex* LowEnter = new Mutex();
static Mutex* lowExit = new Mutex();
static Mutex* Door = new Mutex();

static bool finalCall = false;
static bool inRoom = false;

/* ----------------------------------------------------------- */
/* FUNCTION  GoToParty                                         */
/*    runs the thread of students                              */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    student.threadfuc 									   */
/* ----------------------------------------------------------- */
void student::GoToParty() {
	if (finalCall == true) {
		muxStd->Lock();
			cout << "Student  " << myNum << " terminates" << endl;
		muxStd->Unlock();
		this->Exit();
	}
	//enter room
	LowEnter->Lock(); {
		if (finalCall == true) {
			LowEnter->Unlock();
			muxStd->Lock();
				cout << "Student  " << myNum << " terminates" << endl;
			muxStd->Unlock();
			this->Exit();
		}
		if (inRoom == false || finalCall == true) {
			muxStd->Lock();
				cout << "Student " << myNum << " waits to enter the room" << endl;
			muxStd->Unlock();
			Door->Lock(); {
				if (finalCall == true) {
					LowEnter->Unlock();
					Door->Unlock();
					this->Exit();
				}
				muxStd->Lock();
					cout << "Student " << myNum << " enters the room" << endl;
				muxStd->Unlock();
				numInRoom++;
				this->inParty = true;
			}
			Door->Unlock();
		}
	}LowEnter->Unlock();

	//leave room
	if (this->inParty) {
		lowExit->Lock(); {
			if (finalCall) {
				numInRoom--;
				lowExit->Unlock();
				muxStd->Lock();
					cout << "Student  " << myNum << " terminates" << endl;
				muxStd->Unlock();
				this->Exit();
			}
			muxStd->Lock();
				cout << "Student  " << myNum << "waits to leave ("<< numInRoom << " students in the room)" << endl;
			muxStd->Unlock();
			Door->Lock(); {
				muxStd->Lock();
					cout << "Student " << myNum << " waits to leave the room" << endl;
				muxStd->Unlock();
				numInRoom--;
				this->inParty = false;
			}
			Door->Unlock();
		}lowExit->Unlock();

	}
}

/* ----------------------------------------------------------- */
/* FUNCTION  CheckRoom                                         */
/*    runs the thread of teacher                               */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    student.threadfuc 									   */
/* ----------------------------------------------------------- */
void teacher::CheckRoom(int m,int current) {
	if ((current+1) >= m) {
		finalCall = true;
	}
		Door->Lock(); {
				inRoom = true;
				muxStd->Lock();
					cout << "The landlord checks the room the " << current + 1 << "-th time" << endl;
				muxStd->Unlock();
				if (finalCall == true)
				{
					Door->Unlock();
					while (numInRoom > 0)
					{
						Door->Unlock();
					}
					//muxStd->Lock();
					//cout << "The landlord finishes checking and forces everyone to leave" << endl;
					//muxStd->Unlock();
					this->Exit();
					LowEnter->Unlock();
				}
				if (numInRoom >= this->maxCount) {
					LowEnter->Lock(); {
						Door->Unlock();
						while (numInRoom > 0)
						{
							Door->Unlock();
						}
						muxStd->Lock();
						cout << "The landlord finds " << numInRoom <<" students in the room and breaks up the party"<< endl;
						muxStd->Unlock();
					}LowEnter->Unlock();
				}
				if (numInRoom <= 0) {
					muxStd->Lock();
						cout << "The landlord finds the room has no students and leaves." << endl;
					muxStd->Unlock();
				}
				else {
					muxStd->Lock();
					cout << "The landlord finds there are " <<(current+1) <<"students in the room (condition being good) and leaves." << endl;
					muxStd->Unlock();
				}
				inRoom = false;
		}Door->Unlock();
}
