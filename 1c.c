#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
	int a = mknod("fifo",0744,0);
	if(a==0){
		printf("success");
	}
	else
		printf("error");
}
