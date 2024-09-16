/*
========================================================================================================

Name: 27c
Author: Prajyot Shende
Description: Write a program to execute ls -Rl by the following system calls
        c. execle
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>

int main()
{
	extern char** environ;
	char* a = "/bin/ls";
	execle(a,"ls","-Rl",NULL,environ);
}

/*
========================================================================================================
Output:

./a.out
.:
total 540
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1628 Aug 30 15:53 10.cpp
-rwxrwxr-x 1 prajyot-shende prajyot-shende     30 Aug 30 15:50 10.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   2682 Aug 30 15:53 11.cpp
-rwxrwxr-x 1 prajyot-shende prajyot-shende    400 Aug 30 15:53 11.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1795 Aug 30 15:56 12.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende      0 Aug 28 23:14 12.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1085 Aug 30 15:59 13.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1535 Aug 30 16:03 14.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   4296 Aug 30 16:06 15.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1498 Aug 30 16:10 16a.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende      0 Aug 29 11:08 16a.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1545 Aug 30 16:19 16b.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1125 Aug 30 16:22 19.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1075 Aug 30 15:03 1a.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1162 Aug 30 15:07 1b.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende  16736 Aug 28 18:12 1b.out
-rw-rw-r-- 1 prajyot-shende prajyot-shende    972 Aug 30 15:09 1c.c
-rwxr-xr-x 1 prajyot-shende prajyot-shende      0 Aug 28 19:01 1st.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1002 Aug 30 16:23 20.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    881 Aug 30 16:25 21.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1051 Aug 30 16:28 22.c
-rw-r--r-- 1 prajyot-shende prajyot-shende     40 Aug 30 16:27 22.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende    928 Aug 30 16:29 23.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    999 Aug 30 16:31 24.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1116 Aug 30 16:34 25.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    262 Aug 30 14:57 26b.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    963 Aug 30 16:35 26.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   9485 Aug 30 16:42 27a.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   4761 Aug 30 16:43 27b.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    135 Aug 30 00:57 27c.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    116 Aug 30 00:59 27d.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    139 Aug 30 01:00 27e.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1219 Aug 30 16:41 28.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   2551 Aug 30 16:40 29.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende   2547 Aug 30 15:25 2.cpp
-rwxr-xr-x 1 prajyot-shende prajyot-shende      0 Aug 28 19:01 2nd.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1188 Aug 30 16:38 30.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende    971 Aug 30 15:21 3.cpp
-rwxr-xr-x 1 prajyot-shende prajyot-shende      0 Aug 28 19:01 3rd.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1147 Aug 30 15:24 4.cpp
-rwxr-xr-x 1 prajyot-shende prajyot-shende      0 Aug 28 19:01 4th.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   2523 Aug 30 15:54 5.cpp
-rwxr-xr-x 1 prajyot-shende prajyot-shende      0 Aug 28 19:01 5th.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1085 Aug 30 15:38 6.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende     10 Aug 30 15:42 7a.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende     20 Aug 30 15:42 7b.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1752 Aug 30 15:54 7.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1469 Aug 30 15:45 8.cpp
-rw-rw-r-- 1 prajyot-shende prajyot-shende   1691 Aug 30 15:47 9.cpp
-rwxrwxr-x 1 prajyot-shende prajyot-shende  16032 Aug 30 16:44 a.out
-rwxrwxr-x 1 prajyot-shende prajyot-shende  16000 Aug 30 14:57 b.out
-rw-r--r-- 1 prajyot-shende prajyot-shende      0 Aug 30 15:20 FD
---------- 1 prajyot-shende prajyot-shende      0 Aug 30 15:23 FD.txt
-rw-r--r-- 1 prajyot-shende prajyot-shende      0 Aug 30 15:08 fifo
-rw-rw-r-- 2 prajyot-shende prajyot-shende 154180 Aug 28 18:20 hardlnk
-rw-rw-r-- 2 prajyot-shende prajyot-shende 154180 Aug 28 18:20 hard.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende     54 Aug 28 19:19 read_linebyline.txt
lrwxrwxrwx 1 prajyot-shende prajyot-shende      7 Aug 30 15:01 sftlnk -> filenew


========================================================================================================
*/
