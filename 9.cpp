#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

using namespace std;
int main(){

       
         

	const char* name= "read_linebyline.txt";
	struct stat i;
	int a = stat(name,&i);
   	   cout<<"I-node = "<<i.st_ino<<endl;      
   	   cout<<"No of hardlinks = "<<i.st_mode<<endl;
           cout<<"uid = "<<i.st_nlink<<endl;
           cout<<"gid = "<<i.st_uid<<endl;
           cout<<"size = "<<i.st_gid<<endl;
           cout<<"block-size = "<<i.st_blksize<<endl;
	   cout<<"no of blocks = "<<i.st_blocks<<endl;
 	   cout<<"last access = "<<ctime(&i.st_atime)<<endl;
	   cout<<"last modified = "<<ctime(&i.st_mtime)<<endl;	   
	   cout<<"last changed = "<<ctime(&i.st_ctime)<<endl;












}
