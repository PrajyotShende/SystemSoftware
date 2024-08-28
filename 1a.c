#include<stdio.h>
#include<unistd.h>
int main(){
	int slink = symlink("filenew","sftlnk");
	if(slink == 0){
		printf("softlink created successfully");
	}
	else
	{
		printf("Softlink cannot be created please try again later\n");
		printf("Softlink may already be created, try removing sftlnk and try again\n");
	}
}
