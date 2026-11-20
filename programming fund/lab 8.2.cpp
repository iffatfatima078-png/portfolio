#include<iostream>
using namespace std;

struct student{
	int id;
	char name[15];
	double gpa;
	void GPA ()
	{
		float marks;
		cout<<"Enter marks:";
		cin>>marks;
		if(marks>=60 && marks<=100)
		cout<<"Grand point Average of the student is between 2 and 4"<<endl;
		else
		cout<<"Grand point Average of the student is between 0 and 1.99"<<endl;
	}
};
struct Employee{
	int id;
	char name[15];
};
int main()
{
	student s;
	s.GPA();
	Employee e;
	e.id=12;
	return 0;
}
