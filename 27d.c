#include<stdio.h>
#include<unistd.h>
int main()
{
	char* a = "/bin/ls";
	char* b[] = {a,"-Rl",NULL};
	execv(a,b);
}
