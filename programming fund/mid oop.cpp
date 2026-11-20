#include<iostream>
#include<cstring>
using namespace std;
class student{
	int id;
	int age;
	string name;
	public:
		student(){
		//	id=i;
		//	age=a;
		//	name=n;
}
void getdata(){
			cout<<"enter name: ";
			cin>>name;
			cout<<"enter age: ";
			cin>>age;
			cout<<"enter id: ";
			cin>>id;
		}
		void showdata(){
			cout<<"Name : "<<name<<endl;
			cout<<"Age : "<<age<<endl;
			cout<<"ID: "<<id<<endl;
			
		}
		
};
int main(){
	student s1;
	s1.getdata();
	s1.showdata();
	return 0;
}
