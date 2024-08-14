#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	char z[100];
        int r=0;
 	int read1 = open("read_linebyline.txt",O_RDONLY);
	while(true)
	{
		int a = read(read1,&z[r],1);
		if(a==0) break;
		if(z[r]=='\n')
		{
			write(1,z,r);
			getchar();
			r=0;
			continue;
		}
		r++;
	}
close(read1);	
}
