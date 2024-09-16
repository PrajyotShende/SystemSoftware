/*
========================================================================================================

Name: 12
Author: Prajyot Shende
Description Write a program to find out the opening mode of a file. Use fcntl. 
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
        int a = open("12.txt",O_RDWR|O_CREAT,0666);
	//cout<<a<<endl;
	if(a==-1) cout<<"File Creation failed, Error Error, PLease try again Later\n";
        else cout<<"File Created, File opened, File ok\n";


	int d = fcntl(a,F_GETFL);
	//cout<<d<<endl;
		
	if(d==-1)
	{       
		cout<<"Error in detecting filetype\n";
		getchar();
		cout<<"Closing in 3....\n";
		getchar();
		cout<<"2....\n";
                getchar();
		cout<<"1....\n";
		return 0;
	}
	
	    if (O_RDONLY & d) cout << "RD only" << endl;
	    if (O_WRONLY & d) cout << "WR only" << endl;
	    if (O_RDWR & d) cout << "both rd and write" << endl;
	    if (O_CREAT & d) cout << "creating file" << endl;
	    if (O_APPEND & d) cout << "appending something to the end of file" << endl;
	    if (O_TRUNC & d) cout << "truncating everything in the file" << endl;
	    if (O_EXCL & d) cout << "Exclusive creating and opening of file" << endl;
	    if (O_NONBLOCK & d) cout << "not_blocking mode" << endl;
	    if (O_SYNC & d) cout << "synchronizing write" << endl;
	
    close(a);
    return 0;
}


/*
========================================================================================================
Output:

./a.out
File Created, File opened, File ok
both rd and write

========================================================================================================
*/
