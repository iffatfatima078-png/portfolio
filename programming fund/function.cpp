#include<iostream>
using namespace std;

int square(int);
int main(){
	int n;
	cout<<"enter the value";
	cin>>n;
	for(int i=1; i<=n; i++){
		cout<<square(i);
	}
	return 0;
}
int square(int x){
    return x*x;
	}
