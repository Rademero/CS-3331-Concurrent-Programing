Question 1. 
The logic of my program is, frist I create my
master thread form main. Master's constructor
frists sets it's UserDefinedThreadID to 1 and 
then it takes in the input of n to find all
the primes between 2 and n. It then sets 
Primeindex and MaxSpace count to 0. In master's
ThreadFunc id makes an int index and spacecount.
It then creates a Prime process p2. It then tells
P2 to brgin. Then master uses a while loop to run
throught all the numbers of index to n. In the 
while loop it sends index to P2 and then adds one
to index. after the while loop it sends the end
message then waits for p2 to join. After p2 joins
it prints it's final 3 messages then exits to end
the program. 
The Prime's constructer takes in it's number to 
memorise as well as the prveous number and it's
Id for the channel. It then adds it's number to 
the static array that holds all prime numbers 
that are found. It then adds 1 to the PrimeIndex.
After that the constructor handels it's prints 
and sets up it's channel as well as setting it's
value for isLast to true. The prime's threadFunc
starts by making a int num to take in values.
Then while 1 == 1 it runs the rest of the logic.
It starts by retreving a channel number from the
previous thread. If the number passed in is 1
it checks if it's isLast is true, if it is 
the thread calls exit. if isLast is false it 
waits for the nextPrime to join. If the number 
passed in is not 1 I check if it is divisable by
the threads number. If it is dibisable the thread
ignores the number and restarts back at the 
start of the while loop. If the number is not 
divisable the thread checks it's isLast. If it's 
isLast id true, it creates a new thread passing 
in the number beging checked, the curent thread's 
number, and the curent thread's channel ID + 1 
and sets it's isLast to false. If it's isLast was
false it just sends the number to the next thread

Question 2.
My program works becuse each thread has a prime 
saved. if the number is divisable by one of the 
threads it is not prime and is ignored by the 
program. Each thread over 2 will only recive a 
number if it is not divsable by all of it's 
predacessors. Each channel is set up to where the
Previous thread can send, and the current can 
recive. 

Question 3. 
AllPrimes is an array set to take in 100 inputs.
I know that it is overkill as the program only
takes numbers between 2 and 100. Primeindex is a
staic int with it's value set to 0 at the start 
of the program. I add 1 to it every time a prime
number is added to the the primeindex array as 
it is used to keep the index to proprly add to 
the array. This is a common index counter and 
works no diffrent. MaxSpaceCount is a counter 
to keep track of how many spaces the last thread
needs to print. Each prime number has a varable 
that takes MaxSpaceCount as a defult value in
the constructor, then adds 2 to it. This makes 
sure that each new tread prints 2 lines out from
the previous one. In the master threadfunc it has
a variable index that starts at 3. This is a 
variabel that is used to be passed in to P2. It 
is set to 3 as I have p2 created befor checking 
any value as the program returns prime numbers 
between 2 and n. The constructor of master has
a UserDefinedThreadID set to 1 as it is the frist
thread. MyNum is a public master variable that is
the n of the programe. That is set by the passeed
in n. The thradfuc of Prime has num witch is set
to the number recived by it's channel. Channel is
a snycOneToOne channel where the sender is the 
previous thread. p2 has it's previous thread as 
master. NextPrime is only defined if num is prime.
in the Prime constructor it has ID set to the 
prime number passed in. This is used to print 
what number the thread represents. UserDefinedID
for this thread is sent in by the maker to set
it's channel. SpaceCount is set to the current 
value. This is to make sure the thread prints
in the right line. MaxSpaceCount then has 2 added
to it so the next thread is 2 spaces off of this
thread. name is a char arrray to hold the name of
the channel. The name is set to the prv + "PtoP"
+ num. this makes each name diffrent for the 
channels. prv is set to the last thread number 
by the passed in value. isLast is set to true in
the constructor. This is used to keep track of 
whitch thread is the last thread in the line. it
is only ever set to false if the thread makes 
another thread in whitch it is no longer the last
thread in the line.

Question 4.1
This program would not be able to do this program
with asynchrounous channels as the open end of 
the converstion would end up with a endless loop
or the use of out of order of the final array.

Question 4.2
Once the last thread receives a number it would
of had to be checked by all other threads. This 
would show that the number is not divisable by 
all previous threads. Only this last thread could
be divisable but it is not likely as the number 
gets larger.

Question 4.3
You could have the number to be checked by 
having all previous numbers in the array to 
check if they are diviouable. This program would
change little as instead of threads you could 
use the array. This program is basiclly turning
the array elements into threads to speed up the 
process.

Question 4.4
You do not need a mutex to protect the global 
array of primes as the only time a thread messes
with the array is during the creation. The only 
posible issue would be if 2 threads were created 
at the same time, but my programe dose not allow 
this as each thread needs to check a number befor
a thread is created including new threads begin
created. Thus a mutex is not needed to use the 
global array for prime numbers.

Question 5.
My master waits for P2 to join, all prime 
processes including P2 wait for their secsessor
to join unless the process is the last in the 
line of numbers. an examble is where n is 30
Master prints the complete result:
  2 3 5 7 11 13 17 19 23 29
Master terminates



