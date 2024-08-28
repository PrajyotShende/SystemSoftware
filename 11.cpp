#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
	int a = open("11.txt",O_CREAT|O_RDWR,0777);
        if(a==-1) cout<<"Error in Creating File, please try again later\n";
        else cout<<"File Opened successfully, for now atleast\n";

	int duplicate = dup(a);	

	char x[100] = "Real thing to be inserted in real fil descript(a)\n";
	
	int p = write(a,x,sizeof(x));
	cout<<p<<endl;
	if(p==-1) cout<<"Error in writing from x to a\n";
	else cout<<"Wrote succesfully, WE think\n";
	
	char y[100] ="Fake thing to be inserted in dupliacte fil descriptor(duplicate)\n";
        
	int q = write(duplicate,y,sizeof(y));
	cout<<q<<endl;
	if(q==-1) cout<<"Error in writing from y to duplicate FD which is FD of 'a' itself\n";
        else cout<<"Wrote succesfully, WE think once again\n";


	char z[100] = "Super fake thing\n";	
	
	int doubleduplicate = dup2(a,100);
	
	int r = write(doubleduplicate,z,sizeof(z));
	cout<<r<<endl;
	if(r==-1) cout<<"Error in writing from z to doubledupliacte FD which is FD of 'a' itself\n";
        else cout<<"Wrote succesfully, WE think twice again\n";



	char w[100] = "FCNTL duplicates appending\n";
		
	int superduplicate = fcntl(a,F_DUPFD,1000);

	int s = write(superduplicate,w,sizeof(w));
	cout<<s<<endl;
	if(s==-1) cout<<"Error in writing from s to FD of a\n";
        else cout<<"Wrote succesfully, WE think finally\n";


	cout<<"If no values printed are -1 then all is good, now just check the filw with cat 11.txt\n";
}


