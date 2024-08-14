#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
int main(){
	struct stat inform;
	int fd=open("line.txt",O_RDONLY);
	if(fd==-1){
		printf("error");
	}
	fstat(fd,&inform);
	printf("inode = %ld\n",inform.st_ino);
	printf("hardlink = %ld\n",inform.st_nlink);
	printf("uid = %d\n",inform.st_uid);
	printf("gid = %d\n",inform.st_gid);
	printf("size = %ld\n",inform.st_size);
	printf("blocksize = %ld\n",inform.st_blksize);
	printf("blocks = %ld\n",inform.st_blocks);
	char arr[30];
	time_t atime=inform.st_atim.tv_sec;
	struct tm *atime_tm=localtime(&atime);
	strftime(arr,sizeof(arr),"%Y-%m-%d %H:%M:%S",atime_tm);
	printf("last access = %s\n",arr);
	
	time_t mtime=inform.st_mtim.tv_sec;
	struct tm *mtime_tm=localtime(&mtime);
	strftime(arr,sizeof(arr),"%Y-%m-%d %H:%M:%S",mtime_tm);
	printf("last modified = %s\n",arr);

	time_t ctime=inform.st_ctim.tv_sec;
	struct tm *ctime_tm=localtime(&ctime);
	strftime(arr,sizeof(arr),"%Y-%m-%d %H:%M:%S",ctime_tm);
	printf("last change = %s\n",arr);
	return 0;
}
