#include<stdio.h>
#include<unistd.h>

int main()
{
	extern char** environ;
	char* a = "/bin/ls";
	execle(a,"ls","-Rl",NULL,environ);
}
