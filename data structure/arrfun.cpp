#include<iostream>
using namespace std;

void fun(int array[]){
	for(int i=0; i<5; i++){
		array[i]=array[i]*2;
		cout<<array[i];
	}
}
int main(){
	int arr[5]={1,2,3,4,5};
	for(int i=0; i<5; i++)
	cout<<arr[i]<<endl;
	fun(arr);
	for(int k=0; k<5; k++)
	cout<<arr[k]<<endl;

	
	
	return 0;
}
