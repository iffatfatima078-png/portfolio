#include <iostream>
using namespace std;

int main() {
    int pounds1, shillings1, pence1;
    int pounds2, shillings2, pence2;
    char ch;

    do {
        // Input first amount
        cout << "Enter first amount (pounds.shillings.pence): ";
        char dot; // to read dots
        cin >> pounds1 >> dot >> shillings1 >> dot >> pence1;

        // Input second amount
        cout << "Enter second amount (pounds.shillings.pence):";
        cin >> pounds2 >> dot >> shillings2 >> dot >> pence2;

        // Add pence
        int totalPence = pence1 + pence2;
        int carryShillings = totalPence / 12;
        totalPence %= 12;

        // Add shillings
        int totalShillings = shillings1 + shillings2 + carryShillings;
        int carryPounds = totalShillings / 20;
        totalShillings %= 20;

        // Add pounds
        int totalPounds = pounds1 + pounds2 + carryPounds;

        // Output result
        cout << "Total is :" << totalPounds << "." << totalShillings << "." << totalPence << endl;

        // Ask to continue
        cout << "Do you wish to continue (y/n)? ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');

    return 0;
}

