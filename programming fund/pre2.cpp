#include<iostream>
using namespace std;

int main()
{
	int a[3][2]={{5,6},{8,3},{15,12}};
	int b[3][2]={{8,3},{1,2},{5,10}};
	int c[3][2] ;
	
	cout<<" matrix A:\n";
	for(int i=0; i<3; i++){
	for( int j=0; j<2;j++){
		cout<<a[i][j];
		cout<<"\t";
	}
     cout<<endl;
	}
	cout<<" matrix B:\n";
	for(int i=0; i<3; i++){
	for( int j=0; j<2; j++){
		cout<<b[i][j]<<"\t";
	}
	cout<<endl;
	}
//	cout<<"Addation matrix: \n";
	for(int i=0; i<3; i++){
	for( int j=0; j<2 ;j++){
		c[i][j]=a[i][j]*b[i][j];
	}
	
	}
	cout<<"Sum of matrix:\n";
	for(int i=0; i<3; i++){
	for( int j=0; j<2 ;j++){
	cout<<c[i][j]<<"\t";
	}
	cout<<endl;}
	
	
	
	return 0;
	
}
