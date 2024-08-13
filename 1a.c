#include<stdio.h>
#include<unistd.h>
int main(){
	int slink = symlink("filenew","sftlnk");
	if(slink == 0){
		printf("softlink created");
	}
}
