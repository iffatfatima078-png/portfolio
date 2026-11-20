#include <iostream>
#include <iomanip>  // for setprecision
using namespace std;

int main() {
    double amount, rate;
    int years;

    // Input
    cout << "Enter initial amount: ";
    cin >> amount;

    cout << "Enter number of years: ";
    cin >> years;

    cout << "Enter interest rate (percent per year): ";
    cin >> rate;

    // Convert rate from percent to decimal
    rate = rate / 100;

    // Compound interest calculation using a loop
    for (int i = 1; i <= years; i++) {
        amount = amount + (amount * rate); // or: amount *= (1 + rate);
    }

    // Output final amount with 2 decimal places
    cout << fixed << setprecision(2);
    cout << "At the end of " << years << " years, you will have " << amount << " dollars." << endl;

    return 0;
}

