Question: 1....................................... 
My main program gets an input of size for an array
than create and allocate the shared memory for 
said array. I so this for all of my input arrays. 
I then allocate and create a shared memory for an
out array for my merge. Then I call fork for one
of my programs with an execvp to call one of my
programs. I do this again for my other program
as well. I then tell my program to wait for both
of the processes to finish then I detach and 
deallocte. For my qsort I attach my memory then
I ask if left is less than right. If it is I call
my partion witch is just the center value of my 
array.I then use execvp to recall qsort on both
sides of the partion. each child detaches the 
memory from it's self then exits. Then the main
qsort detaches the memory and exits. The merge 
starts by ataching 3 shared memory adresses to
arrays x,y,out. Then it goes makes children the 
size of array x. within each child the program 
asks 3 questions, if array1[i] < array2[0], then
out[i] = array1[i].if array1[i] > array2[size-1]
then out[i+size] = array1[i]. 
if array2[k] < array1[i] < array[size-1]. then 
out[k+size] = array[i]. It then repets this 
process for the second input array. then it 
detaches the memory from itself and exits.

Question: 2.
Main works becuse I am calling 2 processes to
run both programs then telling main to wait 
before it detaches and deallocates the 
shared memory. Qsort works becuse I am
recusively calling the program to refind
the partition's point in the array on both
sides of the array's partioion so both sides
are not trying to acsess the same data and 
allowing a child to finish befor detaching 
and deallocating the memory. Merge works 
becuse I look at each element of both arrays
and find it's value without and overlap.

Question: 3.
The frist shared memory segment is created
in main and allocated/attached in main.
The memory is then attached to qsort.
qsort attaches then detaches with evey
child. The other 3 are created and 
allocated/attached in main just before
the frist is sent to qsort. The other
3 are attached to merge. None of the
children reattach the memory so no 
need to detach with every child. The 
main process of merge the detaches 
and exits. After BOTH  merge and 
qsort are done the main programe 
detaches then dealloctes the data.
This makes sure their are no memory
issues within the programs.

Question: 4
There is only one race condition within 
the program. This is where one of the children
finish before one of it's own children, I stoped
this by adding another wait stament withing the
child process.

Question 5
I make and array where argv[0] = "qsort"
argv[1] = "0" argv[2] = "7" argv[3] = NULL
this makes ./qsort 0 7

Question 6
I make and array where argv[0] = "merge"
argv[1] = "5" argv[2] = "5" argv[3] = NULL
this makes ./merge 5 6



