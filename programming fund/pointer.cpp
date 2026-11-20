#include<iostream>
using namespace std;

int main(){
	int n;
      int arr[10];
      int i=0;
      arr[i]=(n%10);
      n=n/10;
      i++;
      arr[i]=n;
    cout<<n;
	return 0;
}
