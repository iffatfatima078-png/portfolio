#include<iostream>
using namespace std;

struct student{
	string name;
	int id;
	int marks;
};
int main(){
	student s1;
	cout<<"enter the name : ";
	cin>>s1.name;
	cout<<"enter id : ";
	cin>>s1.id;
	cout<<"enter marks : ";
	cin>>s1.marks;
	
	
	return 0;
}
