#include<iostream>
#include<string>
using namespace std;

class student{
    int id;
    int age;
    string name;

public:
    student(){}   // default constructor

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
        cout<<"Age  : "<<age<<endl;
        cout<<"ID   : "<<id<<endl;
    }
};

int main(){
    student s1;   // now allowed
    s1.getdata(); // user enters values
    s1.showdata();
    return 0;
}
