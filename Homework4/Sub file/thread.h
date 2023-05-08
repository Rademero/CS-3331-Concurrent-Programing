#include <ThreadClass.h>

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 4                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is a header file to be used for later      */
/* -----------------------------------------------------------*/
static Mutex* muxStd = new Mutex();

class student : public Thread 
{
public:
	bool inParty;
	int myNum;
	student(int num);
private:
	void ThreadFunc();
	void GoToParty();
};

class teacher : public Thread
{
public:
	int maxCount;
	int m;
	teacher(int M, int max);
private:
	void ThreadFunc();
	void CheckRoom(int m, int current);
};