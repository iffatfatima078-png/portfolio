#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double initialAmount, finalAmount, rate;
    int years = 0;

    // Input from user
     
    
    cout << "Enter initial amount: ";
    cin >> initialAmount;
    cout << "Enter final amount desired: ";
    cin >> finalAmount;

   

    cout << "Enter interest rate (percent per year): ";
    cin >> rate;

    // Convert percentage to decimal
    rate = rate / 100;

    double currentAmount = initialAmount;

    // Loop until currentAmount reaches or exceeds finalAmount
    while (currentAmount < finalAmount) {
        currentAmount += currentAmount * rate;
        years++;
    }

    // Output the result
    cout << fixed << setprecision(2);
    cout << "It will take " << years << " years to reach " 
         << currentAmount << " dollars." << endl;

    return 0;
}

