#include <iostream>
using namespace std;


// a) Function Declaration / Definition / Calling
void display()
{
    cout << "Welcome to C++ Functions!" << endl;
}

int add(int a, int b)
{
    return a + b;
}


// b) Function Overloading
int sum(int a, int b)
{
    return a + b;
}

float sum(float a, float b)
{
    return a + b;
}


// c) Default Function Arguments
int multiply(int a, int b = 2)
{
    return a * b;
}


// d) Pass by Value
void passByValue(int x)
{
    x = 50;
}


// e) Pass by Reference
void passByReference(int &x)
{
    x = 50;
}


int main()
{
    // a) Function Calling
    display();

    cout << "Addition = " << add(10, 20) << endl;


    // b) Function Overloading
    cout << "Integer Sum = " << sum(10, 20) << endl;
    cout << "Float Sum = " << sum(5.5f, 2.5f) << endl;


    // c) Default Function Arguments
    cout << "Multiplication = " << multiply(5) << endl;


    // d) Pass by Value
    int a = 10;

    cout << "Before Pass by Value = " << a << endl;

    passByValue(a);

    cout << "After Pass by Value = " << a << endl;


    // e) Pass by Reference
    int b = 10;

    cout << "Before Pass by Reference = " << b << endl;

    passByReference(b);

    cout << "After Pass by Reference = " << b << endl;


    return 0;
}
