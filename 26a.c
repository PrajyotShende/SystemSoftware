/*
========================================================================================================

Name: 26a
Author: Prajyot Shende
Description: Write a program to execute an executable program.
        a. use some executable program
        b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	execl("/bin/ls","ls", NULL); 
	return 0;

}

/*
========================================================================================================
Output:

./a.out
10.cpp	14.cpp	 1b.c	  22.txt  27b.c  2nd.txt  5th.txt  a.out     read_linebyline.txt
10.txt	15.cpp	 1b.out   23.c	  27c.c  30.c	  6.cpp    b.out     sftlnk
11.cpp	16a.cpp  1c.c	  24.c	  27d.c  3.cpp	  7a.txt   FD
11.txt	16a.txt  1st.txt  25.c	  27e.c  3rd.txt  7b.txt   FD.txt
12.cpp	16b.cpp  20.c	  26b.c   28.c	 4.cpp	  7.cpp    fifo
12.txt	19.c	 21.c	  26.c	  29.c	 4th.txt  8.cpp    hardlnk
13.cpp	1a.c	 22.c	  27a.c   2.cpp  5.cpp	  9.cpp    hard.txt


========================================================================================================
*/
