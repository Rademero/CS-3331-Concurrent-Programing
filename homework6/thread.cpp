#include "thread.h"
#include <iostream>
#include <functional>
#include <cstring>
#include<stdio.h>
#include <ThreadClass.h> 
using namespace std;

static int AllPrimes[25];
//static int Primeindex;
static int MaxSpaceCount;

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 6                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program counts all prime numbers between 2 and n   */
/* -----------------------------------------------------------*/
/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of Master                                */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */
void Master::ThreadFunc()
{
	Thread::ThreadFunc(); // required
	int index = 3;
	//create p2
	Prime* p2 = new Prime(2, 1,1);
	p2->Begin();
	//sends all numbers
	while (index <= myNum) {
	
		p2->channel->Send(&index, sizeof(int));
		muxStd->Lock();
			cout << "Master sends " << index << " to P2" << endl;
		muxStd->Unlock();
		index++;
	}
	//send end
	index = 1;
	p2->channel->Send(&index, sizeof(int));
	muxStd->Lock();
	cout << "Master sends END" << endl;
	muxStd->Unlock();
	p2->Join();
	//final prints
	muxStd->Lock();
		cout << "Master prints the complete result:" << endl << " ";
	muxStd->Unlock();

	int i = 0;
	muxStd->Lock();
	//for (i = 0; i < Primeindex; i++) {
	while (AllPrimes[i] != 0 && AllPrimes[i] != NULL && AllPrimes[i] < 100)
	{
		cout << " " << AllPrimes[i];
		i++;
	}
		
	//}
	cout << endl << "Master terminates" << endl;
	muxStd->Unlock();
	Exit();
}

/* ----------------------------------------------------------- */
/* FUNCTION  Master                                            */
/*     This method is to set up the Master thread              */
/* PARAMETER USAGE :                                           */
/*     num: input for the numbers to be checked                */
/* FUNCTION CALLED :                                           */
/*    thread-main.main 										   */
/* ----------------------------------------------------------- */

Master::Master(int num) {
	//basic setup for all threads/static vars
	UserDefinedThreadID = 1;
	myNum = num;
	muxStd->Lock();
		cout << "Master starts" << endl;
	muxStd->Unlock();
	//Primeindex = 0;
	MaxSpaceCount = 2;
}
/* ----------------------------------------------------------- */
/* FUNCTION  ThreadFunc                                        */
/*    runs the thread of Prime                                 */
/* PARAMETER USAGE :                                           */
/*		none                                                   */
/* FUNCTION CALLED :                                           */
/*    thread.Master.ThreadFunc and thread.prime.ThreadFunc 	   */
/* ----------------------------------------------------------- */
void Prime::ThreadFunc()
{
	Thread::ThreadFunc(); // required
	int num;
	int i;
	while (1) {
		//get input
		channel->Receive(&num, sizeof(int));
		//end of data
		if (num == 1) {
			muxStd->Lock();
			for (i = 0; i < spaceCount; i++) {
				cout << " ";
			}
			cout << "P" << ID << " receives END" << endl;
			muxStd->Unlock();

			if (isLast) {
				Exit();
			}
			nextPrime->channel->Send(&num, sizeof(int));
			nextPrime->Join();
			Exit();
		}
		else {//numbers to be checked

			muxStd->Lock();
			for (i = 0; i < spaceCount; i++) {
				cout << " ";
			}
			cout << "P" << ID << " receives " << num << endl;
			muxStd->Unlock();
			//multiple of k
			if (num % ID == 0) {
				//ignores k
				muxStd->Lock();
				for (i = 0; i < spaceCount; i++) {
					cout << " ";
				}
				cout << "P" << ID << " ignores " << num << endl;
				muxStd->Unlock();
			}//not a multiple of k
			else {
				if (isLast) {//makes new process(last process in line)
					nextPrime = new Prime(num, ID, UserDefinedThreadID++);

					muxStd->Lock();
					for (i = 0; i < spaceCount; i++) {
						cout << " ";
					}
					cout << "P" << ID << " creates P" << num << endl;
					muxStd->Unlock();

					nextPrime->Begin();
					isLast = false;
				}//sends to next process
				else {
					muxStd->Lock();
					for (i = 0; i < spaceCount; i++) {
						cout << " ";
					}
					cout << "P" << ID << " sends " << num << " to P" << nextPrime->ID << endl;
					muxStd->Unlock();
					nextPrime->channel->Send(&num, sizeof(int));
				}
			}
		}

	}
	Exit();
}

/* ----------------------------------------------------------- */
/* FUNCTION  Prime                                             */
/*     This method is to set up the Prime                      */
/* PARAMETER USAGE :                                           */
/*     num: Prime number to memorize       
       last: The last prime number to be memorized 
	   UserID: This thread's ID for the channels               */
/* FUNCTION CALLED :                                           */
/*    thread.Master.ThreadFunc and thread.prime.ThreadFunc 	   */
/* ----------------------------------------------------------- */
Prime::Prime(int num, int last, int UserID) {
	//sets the input for the array of prime numbers
	AllPrimes[UserID-1] = num;
	//Primeindex++;
	//channel ID setup
	ID = num;
	myIndex = UserID - 1;
	UserDefinedThreadID = UserID;
	prv = last;
	//prints memory statments
	spaceCount = MaxSpaceCount;
	MaxSpaceCount += 2;
	int i; 
	muxStd->Lock();
	for (i = 0; i < spaceCount;i++) {
		cout << " ";
	}
		cout << "P" << num << " starts and memorizes " << num << endl;
	muxStd->Unlock();

	//makes the channel
	const char* name = prv + "PtoP" + num;
	channel = new SynOneToOneChannel(name, UserDefinedThreadID-1, UserDefinedThreadID);
	isLast = true;

}
