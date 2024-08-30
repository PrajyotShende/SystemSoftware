#include<stdio.h>
#include<unistd.h>
int main(){
	char *a = "ls";
	execlp(a,"ls","-Rl",NULL);
}
