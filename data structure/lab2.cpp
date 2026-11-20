#include <iostream>
using namespace std;


// a) Defining a Structure
struct Student
{
    int rollNo;
    string name;
    float marks;

    // Nested Structure
    struct Address
    {
        string city;
        int houseNo;
    };

    Address address;
};


// c) Structure Implementation as Public and Private
struct Result
{
public:
    int totalMarks;

private:
    int obtainedMarks;

public:
    void setMarks(int marks)
    {
        obtainedMarks = marks;
    }

    void displayMarks()
    {
        cout << "Obtained Marks: " << obtainedMarks << endl;
    }
};


// d) Nested Structure in Context of Inheritance
struct ResultStudent : public Student
{
    float percentage;

    void display()
    {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks << endl;

        // Nested Structure Access
        cout << "City: " << address.city << endl;
        cout << "House No: " << address.houseNo << endl;

        cout << "Percentage: " << percentage << "%" << endl;
    }
};


int main()
{
    // a) Defining a Structure
    Student s1;


    // b) Accessing a Structure
    s1.rollNo = 101;
    s1.name = "Ali";
    s1.marks = 85.5;

    cout << "Roll No: " << s1.rollNo << endl;
    cout << "Name: " << s1.name << endl;
    cout << "Marks: " << s1.marks << endl;


    cout << "\n--- Public and Private ---" << endl;

    // c) Public and Private
    Result r1;

    r1.totalMarks = 100;
    r1.setMarks(85);

    cout << "Total Marks: " << r1.totalMarks << endl;
    r1.displayMarks();


    cout << "\n--- Nested Structure and Inheritance ---" << endl;

    // d) Nested Structure + Inheritance
    ResultStudent r2;

    r2.rollNo = 102;
    r2.name = "Ahmed";
    r2.marks = 90;

    r2.address.city = "Rawalpindi";
    r2.address.houseNo = 25;

    r2.percentage = 90;

    r2.display();


    return 0;
}
