#include<iostream>
using namespace std;
int array(int arr[], int size){
int total=0;
float avg=size;
for(int i=0;i<size; i++){
total+=arr[i];
avg=total/size;
}
return avg;
}

int main(){
int myarray[]={1,2,3,4};
int size=4;
int result=array(myarray,size);
cout<<result;

	
	return 0;
}
