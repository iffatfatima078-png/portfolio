#include <iostream>
#include<cstring>
using namespace std;

struct Address {
    int Zipcode;
    string city;
    string street;
};

struct Student {
    string name;
    int rollno;
    Address address;
};

int main() {
    Student s[3];

    // Input loop
    for(int i = 0; i < 3; i++) {
       

        cout << "Enter the student Name " << (i + 1) << ": ";
        cin>>s[i].name;

        cout << "Enter the student Roll No " << (i + 1) << ": ";
        cin >> s[i].rollno;

        cout << "Enter the student Zipcode " << (i + 1) << ": ";
        cin >> s[i].address.Zipcode;
       

        cout << "Enter the student City " << (i + 1) << ": ";
       cin>> s[i].address.city; 

        cout << "Enter the student Street " << (i + 1) << ": ";
       cin>> s[i].address.street; 

        cout << endl;
    }

    // Output loop
    cout << "Student Details:" << endl;
    for(int i = 0; i < 3; i++) {
        cout << "Student " << (i + 1) << ":" << endl;
        cout << "Name: "   << s[i].name << endl;
        cout << "Roll No: "<< s[i].rollno << endl;
        cout << "Address:" << endl;
        cout << "Zipcode: "<< s[i].address.Zipcode << endl;
        cout << "City: "   << s[i].address.city << endl;
        cout << " Street: "<< s[i].address.street << endl << endl;
    }

    return 0;
}

