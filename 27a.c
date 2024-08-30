#include<stdio.h>
#include<unistd.h>
int main()
{
	char* p = "/bin/ls";
	execl(p,"ls","-Rl",NULL);
}
