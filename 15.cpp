#include <bits/stdc++.h>
using namespace std;
extern char **environ;
int main()
{
	cout<<*environ<<endl;
	char **z = environ;
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"Everything will be printed now\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";

	while(*z!= NULL){
		cout << *z++ << endl;
		
	}
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"\n";
	cout<<"Finished Printing\n";

}

