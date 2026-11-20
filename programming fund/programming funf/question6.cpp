#include <iostream>
using namespace std;

int main() {
    unsigned int num;    // input number
    unsigned long long fact; // to hold the factorial (use long long for large results)

    do {
        cout << "Enter a number: ";
        cin >> num;

        if (num == 0) {
            cout << "Program terminated." << endl;
            break;
        }

        fact = 1;
        for (int j = num; j > 1; j--) {
            fact *= j;
        }

        cout << "Factorial is: " << fact << endl;

    } while (true); // runs until user enters 0

    return 0;
}

