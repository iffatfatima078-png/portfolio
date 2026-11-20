#include <iostream>
#include <iomanip> // for setprecision and fixed

using namespace std;

int main() {
    int choice;
    double temperature, converted;

    // Prompt user for conversion choice
    cout << "Type 1 to convert Fahrenheit to Celsius,\n";
    cout << "2 to convert Celsius to Fahrenheit: ";
    cin >> choice;

    if (choice == 1) {
        // Fahrenheit to Celsius
        cout << "Enter temperature in Fahrenheit: ";
        cin >> temperature;
        converted = (temperature - 32) * 5.0 / 9.0;
        cout << fixed << setprecision(6); // Show 6 decimal places
        cout << "In Celsius that’s " << converted << endl;
    } else if (choice == 2) {
        // Celsius to Fahrenheit
        cout << "Enter temperature in Celsius: ";
        cin >> temperature;
        converted = (temperature * 9.0 / 5.0) + 32;
        cout << fixed << setprecision(6); // Show 6 decimal places
        cout << "In Fahrenheit that’s " << converted << endl;
    } else {
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    return 0;
}

