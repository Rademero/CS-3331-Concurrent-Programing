#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/* ----------------------------------------------------------- */
/* NAME : Michael Romero                         User ID: maromero */
/* DUE DATE : 2/10/2021                                       */
/* PROGRAM ASSIGNMENT # 1                                       */
/* FILE NAME : prog1										   */
/* PROGRAM PURPOSE :                                           */
/*    This program has 4 main functons that run concurrentlly.*/
/*Function 1 is a recursive Fibonacci*/
/*fuction 2 is a Buffon's Needle and the probablitty of a neddle breacking the plan*/
/*function 3 finds the area of an eclipse*/
/*function 4 is a simple pinball macheine*/
/* ----------------------------------------------------------- */


/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This method is used to make 4 child prosses to run      */
/* PARAMETER USAGE :                                           */
/*    n -used to find the n-th input for Fibonacci
	  r -the number of needles thrown for Buffon's Needle 
	  a -SimiMajor axis of an eclipse
	  b -SimiMinor axis of an eclipse
	  s -Total number of random pairs within an eclipse
	  x -Number of bins for a pinballMachine
	  y -Number of balls droped for the pinballMachine         */
/* FUNCTION CALLED :                                           */
/*    none											           */
/* ----------------------------------------------------------- */
int main(int argc, char** argv)
{
	//args check
	if (argc < 7)
	{
		printf("Usage: prog1 <n> <r> <a> <b> <s> <x> <y>\n");
		return 0;
	}
	//Var initialization
	int n = atoi(argv[1]);
	int r = atoi(argv[2]);
	int a = atoi(argv[3]);
	int b = atoi(argv[4]);
	int s = atoi(argv[5]);
	int x = atoi(argv[6]);
	int y = atoi(argv[7]);

	srand(time(NULL));//seed for random number rand()
	//simple var check
	printf("Main Process Started\nFibonacci Input            = %d\nBuffon's Needle Iterations = %d\nTotal random Number Pairs  = %d\n"
		"Semi-Major Axis Length     = %d\nSemi-Minor Axis Length     = %d\nNumber of Bins             = %d\nNumber of Ball Droppings   = %d\n", n, r, s, a, b, x, y);
	//process 1
	pid_t pid1;
	pid1 = fork();
	if (pid1 < 0) {
		printf("Oops!");
	}
	else if (pid1 == 0) {//child
		char buf[100];
		int res = fib(n);
		sprintf(buf, "   Fibonacci Process Started\n   Input Number %1d\n   Fibonacci Number f(10) is %1d\n   Fibonacci Process Exits\n", n, res);
		write(1, buf, strlen(buf));
		exit(1);//stops zombie tasks
	}

	char buf[100];
	sprintf(buf, "Fibonacci Process Created\n");
	write(1, buf, strlen(buf));
//process 2
	pid_t pid2;
	pid2 = fork();
	if (pid2 < 0) {
		printf("Oops!");
	}
	else if (pid2 == 0) {//child
		buffonNeedle(r);
		exit(1);//stops zombie tasks 
	}

	sprintf(buf, "Buffon's Needle Process Created\n");
	write(1, buf, strlen(buf));
//process 3
	pid_t pid3;
	pid3 = fork();
	if (pid3 < 0) {//child
		printf("Oops!");
	}
	else if (pid3 == 0) {
		areaOfEllipse(a, b, s);
		exit(1);//stops zombie tasks
	}

	sprintf(buf, "Ellipse Area Process Created\n");
	write(1, buf, strlen(buf));
//process 4
	pid_t pid4;
	pid4 = fork();
	if (pid4 < 0) {
		printf("Oops!");
	}
	else if (pid4 == 0) {//child
		pinball(x, y);
		exit(1);//Stops zombie task
	}

	sprintf(buf, "Pinball Process Created\nMain Process Waits\n");
	write(1, buf, strlen(buf));
//wait for all processes to end 	
	int i;
	for ( i = 0; i < 4; i++)
	{
		pid_t pid_child;
		int status;
		pid_child = wait(&status);
	}
//end
	sprintf(buf, "Main Process Exits\n");
	write(1, buf, strlen(buf));
}

/* ----------------------------------------------------------- */
/* FUNCTION  fib                                               */
/*     This method is used to find the n-th number of a Fibonacci */
/* PARAMETER USAGE :                                           */
/*    n -used to find the n-th input for Fibonacci             */
/* FUNCTION CALLED :                                           */ 
/*    main											           */
/* ----------------------------------------------------------- */
int fib(int n) {
	if ((n == 1) || (n == 0))
	{
		return n;//end of recursion 
	}
	else
	{
		return (fib(n - 1) + fib(n - 2));//recusive call of fiboancci
	}
}
/* ----------------------------------------------------------- */
/* FUNCTION  buffonNeedle                                      */
/*     This method is used to the probablitty of a needle crossing a line */
/* PARAMETER USAGE :                                           */
/*    r -Number of needles thrown                              */
/* FUNCTION CALLED :                                           */
/*    main											           */
/* ----------------------------------------------------------- */
 buffonNeedle(int r) {
	 char buf[100];
	 sprintf(buf, "      Buffon's Needle Process Started\n      Input Number %d\n",r);
	 write(1, buf, strlen(buf));
	int t = 0;//number of needles across the line
	int i;
	for (i = 0; i < r; i++) {
		float d =(float) rand() / (RAND_MAX);// random number [0,1)
		float a = (float) rand() / (RAND_MAX/ (2 * acos(-1.0)));// random number [0,2pie)
		float results = (d + sin(a));//pos
		if (results < 0.0f || results > 1.0f) {//is across the line
			t++;
		}
	}
	float prob = ((float) t / (float) r);//total number of hits / by the number of throws
	sprintf(buf, "      Estimated Probability is %.5f\n      Buffon's Needle Process Exits\n", prob);
	write(1, buf, strlen(buf));
	//end
}
 /* ----------------------------------------------------------- */
 /* FUNCTION  areaOfEllipse                                     */
 /*     This method is used to find the area of an ellipse      */
 /* PARAMETER USAGE :                                           */
 /*   a -SimiMajor axis of an eclipse
	  b -SimiMinor axis of an eclipse
	  s -Total number of random pairs within an eclipse         */
 /* FUNCTION CALLED :                                           */
 /*    main											            */
 /* ----------------------------------------------------------- */
 areaOfEllipse(int a, int b, int s) {
	 char buf[100];
	 sprintf(buf, "         Ellipse Area Process Started\n         Total random Number Pairs %d\n         Semi-Major Axis Length %d\n         Semi-Minor Axis Length %d\n", s, a, b);
	 write(1, buf, strlen(buf));
	 int i;
	 int t = 0;
	 for (i = 0; i < s; i++) {//test for each pair 
		 float x = (float) rand() /(RAND_MAX / (float) a);//random number [0,a)
		 float y = (float) rand() / (RAND_MAX / (float)b);//random number [0,b)

		 float resu = ((float)((x * x) / (a * a))) + ((float)((y * y) / (b * b)));//x^2/a^2 + y^2/b^2
		 if (resu  <= 1.0f) {// if less then 1 then the point is in the ellipse
			 t++;
		 }
	 }
	 sprintf(buf, "         Total Hits %d\n", t);
	 write(1, buf, strlen(buf));
	 float area = (((float) t /(float) s) * a * b) * 4;//(t/s)ab*4
	 float areaReal = (float)a * (float)b * acos(-1.0);//ab*pie
	 sprintf(buf, "         Estimated Area is %.5f\n         Actual Area is %.5f\n         Ellipse Area Process Exits\n", area , areaReal);
	 write(1, buf, strlen(buf));
	 //end
 }

 /* ----------------------------------------------------------- */
/* FUNCTION  pinball                                            */
/*     This method is used to simulate a very simple pinball machine*/
/* PARAMETER USAGE :                                           */
/*    x -Number of bins for a pinballMachine
	  y -Number of balls droped for the pinballMachine         */
/* FUNCTION CALLED :                                           */
/*    main											           */
/* ----------------------------------------------------------- */
 pinball(int x, int y) {
	 char buf[100];
	 sprintf(buf, "Simple Pinball Process Started\nNumber of Bins %d\nNumber of Ball Droppings %d\n", x , y);
	 write(1, buf, strlen(buf));
	 int i;
	 int buckets[x];//an array to repersent the buckets and the amount of balls in them
	 //sets all of the array to 0
	 for (i = 0; i < x; i++) {
		 buckets[i] = 0;
	 }
	 //Throws all of the balls
	 for (i = 0; i < y; i++) {
		 int j;
		 int overBin = 0;//Keeps track of the ball
		 for ( j = 0; j < (x-1); j++)//simulates pins of the pinball 
		 {
			 int pins = (rand() % 2);//random number that is 0 or 1
			 if (pins == 1) {//if 0 the ball is still over the same bin
				 overBin++;//if 1 the ball goes 1 to the right
			 }
		 }
		 buckets[overBin] = buckets[overBin] + 1;//ball in bin i goes up by 1
	 }
	 //finds the bin with the highest amount of balls
	 int Largest = 0;
	 for (i = 0; i < x; i++) {
		 if (Largest < buckets[i]) {
			 Largest = buckets[i];
		}
	 }
	 //used to print the histograme and other parts
	 for (i = 0; i < x; i++) {
		 float prob = ((float)buckets[i] / (float)y) * (float) 100;
		 //finds the amount of * for the histograme
		 int Hiscount =(int) (round(((float)buckets[i] / (float)Largest) * (float)100));
		 Hiscount = (int)(Hiscount / 2);
		 //prints bin#, balls and the balls in the bin
		 sprintf(buf, "%3d-(%7d)-(%5.2f%%)|", i + 1, buckets[i],prob);
		 write(1, buf, strlen(buf));
		 //prints the histogram
		 int j;
		 for (j = 0; j < Hiscount - 1;j++) {
			 sprintf(buf, "*");
			 write(1, buf, strlen(buf));
		 }
		 sprintf(buf, "*\n");
		 write(1, buf, strlen(buf));
	 }
	 sprintf(buf, "Simple Pinball Process Exits\n");
	 write(1, buf, strlen(buf));
	 //end
 }

