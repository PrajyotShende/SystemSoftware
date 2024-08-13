#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[20];
	int s = read(0,a,20);
	if(s==-1) cout<< "error"<<endl;
	else cout<<s<<" bites read properly"<<endl;

        s = write(1,a,20);
	if(s==-1) cout<<"error in writing"<<endl;
}




