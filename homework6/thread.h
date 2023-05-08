#include <ThreadClass.h>

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 6                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is a header file to be used for later      */
/* -----------------------------------------------------------*/
static Mutex* muxStd = new Mutex();

class Master : public Thread
{
public:
	Master(int num);
	int myNum;
	SynOneToOneChannel* channel;
	int index;
private:
	void ThreadFunc();
};

class Prime : public Thread
{
public:
	Prime(int num, int last, int UserID);
	int ID;
	int prv;
	int myIndex;
	SynOneToOneChannel* channel;
	bool isLast;
	Prime* nextPrime;
	int spaceCount;
private:
	void ThreadFunc();
};


