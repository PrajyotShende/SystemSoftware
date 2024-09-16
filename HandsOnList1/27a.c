/*
========================================================================================================

Name: 27a
Author: Prajyot Shende
Description: Write a program to execute ls -Rl by the following system calls
	a. execl
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main()
{
	char* p = "/bin/ls";
	execl(p,"ls","-Rl",NULL);
}

/*
========================================================================================================
Output:

./a.out
.:
total 528
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
-rw-rw-r-- 1 prajyot-shende prajyot-shende    101 Aug 30 00:53 27a.c
-rw-rw-r-- 1 prajyot-shende prajyot-shende     96 Aug 30 00:55 27b.c
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
-rwxrwxr-x 1 prajyot-shende prajyot-shende  15960 Aug 30 16:42 a.out
-rwxrwxr-x 1 prajyot-shende prajyot-shende  16000 Aug 30 14:57 b.out
-rw-r--r-- 1 prajyot-shende prajyot-shende      0 Aug 30 15:20 FD
---------- 1 prajyot-shende prajyot-shende      0 Aug 30 15:23 FD.txt
-rw-r--r-- 1 prajyot-shende prajyot-shende      0 Aug 30 15:08 fifo
-rw-rw-r-- 2 prajyot-shende prajyot-shende 154180 Aug 28 18:20 hardlnk
-rw-rw-r-- 2 prajyot-shende prajyot-shende 154180 Aug 28 18:20 hard.txt
-rw-rw-r-- 1 prajyot-shende prajyot-shende     54 Aug 28 19:19 read_linebyline.txt
lrwxrwxrwx 1 prajyot-shende prajyot-shende      7 Aug 30 15:01 sftlnk -> filenew


/*
========================================================================================================

Name: 27a
Author: Rakshit Patel
Description: Write a program to execute ls -Rl by the following system calls
	a. execl
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>

int main() {
	execl( "/bin/ls", "ls", "-Rl", NULL );

	return 0;
}

/*
========================================================================================================
Output:

 ./a.out
.:
total 220
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1873 Aug 29 23:25 10.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel    30 Aug 29 23:23 10_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2135 Aug 29 23:45 11.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel   137 Aug 29 23:44 11_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1709 Aug 29 23:57 12.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel     0 Aug 13 22:24 12_file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1281 Aug 30 00:02 13.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1749 Aug 30 00:09 14.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  4021 Aug 30 00:12 15.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1555 Aug 30 11:12 16a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1463 Aug 30 11:12 16b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1855 Aug 30 11:24 17a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2306 Aug 30 11:24 17b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  4476 Aug 30 11:38 18.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1085 Aug 30 11:49 19.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1092 Aug 30 00:13 1a.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1204 Aug 29 22:31 1b.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1218 Aug 29 22:34 1c.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel   971 Aug 30 11:50 20.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1136 Aug 30 11:58 21.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1177 Aug 30 12:06 22.c
-rw-r--r-- 1 rakshit-patel rakshit-patel    50 Aug 30 12:05 22file.txt
-rw-rw-r-- 1 rakshit-patel rakshit-patel   836 Aug 30 12:09 23.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   943 Aug 30 12:11 24.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1150 Aug 30 12:18 25.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   851 Aug 30 12:32 26a.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1009 Aug 30 12:32 26b.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   105 Aug 29 17:46 27a.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   100 Aug 29 18:02 27b.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   139 Aug 29 18:01 27c.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   125 Aug 29 18:01 27d.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   121 Aug 29 18:00 27e.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   462 Aug 29 18:31 28.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2036 Aug 29 19:00 29.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2251 Aug 29 22:41 2.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel   577 Aug 29 19:51 30.c
-rw-rw-r-- 1 rakshit-patel rakshit-patel   967 Aug 30 00:13 3.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1226 Aug 29 22:53 4.cpp
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:52 4_file
-rw-rw-r-- 1 rakshit-patel rakshit-patel  2040 Aug 29 22:57 5.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1258 Aug 29 23:01 6.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1773 Aug 29 23:08 7.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1438 Aug 29 23:15 8.cpp
-rw-rw-r-- 1 rakshit-patel rakshit-patel  1864 Aug 29 23:20 9.cpp
-rwxrwxr-x 1 rakshit-patel rakshit-patel 15960 Aug 30 12:37 a.out
-rwxrwxr-x 1 rakshit-patel rakshit-patel 16608 Aug 30 12:31 b.out
-r----x--t 1 rakshit-patel rakshit-patel     0 Aug 29 22:46 creat_file
--wxrw---t 1 rakshit-patel rakshit-patel     0 Aug 29 22:34 fifo_file
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_1
-rw-r--r-- 2 rakshit-patel rakshit-patel     0 Aug 30 12:31 file1.txt
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_2
-rw-r--r-- 1 rakshit-patel rakshit-patel    40 Aug 29 23:06 file2.txt
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_3
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_4
---------- 1 rakshit-patel rakshit-patel     0 Aug 29 22:55 file_5
-rw-r--r-- 2 rakshit-patel rakshit-patel     0 Aug 30 12:31 hl_file1
-rw-rw-r-- 1 rakshit-patel rakshit-patel     0 Aug 29 22:28 hltemp
-rw-rw-r-- 1 rakshit-patel rakshit-patel    24 Aug 30 11:37 records.txt
lrwxrwxrwx 1 rakshit-patel rakshit-patel     9 Aug 29 22:23 sf_file1 -> file1.txt
-rw-r--r-- 1 rakshit-patel rakshit-patel     0 Aug 29 22:48 tempfile.txt
-rwxrwxr-x 1 rakshit-patel rakshit-patel     8 Aug 30 11:24 tickets.txt

========================================================================================================
*/

