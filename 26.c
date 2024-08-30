#include<stdio.h>
#include<unistd.h>
int main(int argc,char** argv)
{
        if(argc<2)
        {
                printf("PLease enter the file name correctly\n" );
                return 0;
        }
        execl(argv[1],argv[2], NULL );
}
