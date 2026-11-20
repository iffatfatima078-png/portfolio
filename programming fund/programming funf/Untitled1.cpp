#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int lines,columns,enter_number;
	cout<<"Enter Number : ";
	cin>>enter_number;
	for( lines=0; lines<20;lines++)
	{
		for( columns=1;columns<=10;columns++)
		cout<<setw(7)<<(enter_number*(10*lines+columns));
		cout<<endl;
	}
	return 0;
}
