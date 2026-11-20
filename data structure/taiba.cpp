#include<iostream>
using namespace std;
int main(){
int a[]={10,20,30,40,50,60,70,80,90,100};
int size=10;
int low=0;
int high=size-1;
int key=20;

while(low<=high){
	int mid=(low+high)/2;
	if(key==a[mid]){
		cout<<"key found at : "<<mid;
		break;
	}
	else if (key > a[mid]){
		low=mid+1;
	}
	else{
		high=mid-1;
	}
}
	return 0;
}
