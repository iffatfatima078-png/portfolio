#include <iostream>
using namespace std;

int main()
{
    int choice;
    float temp;

    cout << "Type 1 to convert Fahrenheit to Celsius,\n";
    cout << "Type 2 to convert Celsius to Fahrenheit: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            cout << "Enter temperature in Fahrenheit: ";
            cin >> temp;
            cout << "In Celsius that's " << (temp - 32) * 5 / 9 << endl;
            break;

        case 2:
            cout << "Enter temperature in Celsius: ";
            cin >> temp;
            cout << "In Fahrenheit that's " << (temp * 9 / 5) + 32 << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}

