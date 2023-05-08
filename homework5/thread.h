#include <ThreadClass.h>

/* -----------------------------------------------------------*/
/* NAME : Michael Romero                    User ID: maromero */
/* DUE DATE : 3/17/2021                                       */
/* PROGRAM ASSIGNMENT # 5                                     */
/* FILE NAME : thread      									  */
/* PROGRAM PURPOSE :                                          */
/*    This program is a header file to be used for later      */
/* -----------------------------------------------------------*/
static Mutex* muxStd = new Mutex();

class Elf : public Thread
{
public:
	Elf(int num);
	int myNum;
private:
	void ThreadFunc();
};

class Reindeer : public Thread
{
public:
	Reindeer(int num);
	int myNum;
private:
	void ThreadFunc();
};
class Santa : public Thread
{
public:
	int reason;
	Santa(int num,int max);
	int toyCount;
private:
	void ThreadFunc();
};


class workFlow :public Monitor
{
public:
	void AskQuestion(int num);
	void ReindeerBack(int num, int max);
	void WaitOthers(int num);
	void WaitSleigh();
	void FlyOff();
	void Sleep();
	void AnswerElfs();
	void GatherAll();
	void SleighReady();
	void Delivered(int num);
	Condition* wakeSanta;
	Condition* questionAnswered;
	Condition* lineCleared;
	Condition* Gather;
	Condition* sleightsReady;
	Condition* takeOff;
	workFlow();
private:
	int elfArr[3];
};
