#include<iostream>
using namespace std;
struct Test 
{
	int x,y;
	void set(int a,int b)
	{ 
	x=a;
	y=b;
	}
	void get()
	{
		cout<<"The value of X is: "<<x<<endl;
		cout<<"the Value of Y is: " <<y<<endl;
	}
};
int main()
{
	Test obj; // in this line t is capital while we declear small t
	obj.set(10,20);
	obj.get();
	return 0;
}
