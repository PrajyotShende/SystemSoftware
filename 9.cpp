/*
========================================================================================================

Name: 9
Author: Prajyot Shende
Description: Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

using namespace std;
int main()
{

	const char* name= "read_linebyline.txt";
	struct stat i;
	int a = stat(name,&i);
   	   cout<<"I-node = "<<i.st_ino<<endl;      
   	   cout<<"#hardlinks = "<<i.st_mode<<endl;
           cout<<"uid = "<<i.st_nlink<<endl;
           cout<<"gid = "<<i.st_uid<<endl;
           cout<<"size = "<<i.st_gid<<endl;
           cout<<"block-size = "<<i.st_blksize<<endl;
	   cout<<"#blocks = "<<i.st_blocks<<endl;
 	   cout<<"last_access = "<<ctime(&i.st_atime)<<endl;
	   cout<<"last_modified = "<<ctime(&i.st_mtime)<<endl;	   
	   cout<<"last_changed = "<<ctime(&i.st_ctime)<<endl;

}


/*========================================================================================================
Output:-

./a.out
I-node = 2381989
#hardlinks = 33204
uid = 1
gid = 1000
size = 1000
block-size = 4096
#blocks = 8
last_access = Thu Aug 29 19:23:19 2024

last_modified = Wed Aug 28 19:19:28 2024

last_changed = Wed Aug 28 19:19:28 2024

========================================================================================================
*/
