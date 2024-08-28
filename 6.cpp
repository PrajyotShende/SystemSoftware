#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[20];
	int s = read(0,a,20);
	if(s==-1) cout<< "errorrrrrrrrrrrr"<<endl;
	else cout<<s<<" bites read properly so chill"<<endl;

        s = write(1,a,s);
	if(s==-1) cout<<"but some error in writing bro, so work harder"<<endl;
}




