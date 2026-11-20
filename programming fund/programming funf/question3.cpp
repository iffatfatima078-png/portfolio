#include <iostream>
#include <conio.h>  // For getche()
using namespace std;

int main() {
    char ch;
    long total = 0;

    cout << "Enter a number: " ;

    for (int i = 1; i <= 6; i++) {
        ch = getche();  // Read one character and display it
        if (ch < '0' || ch > '9') {
            break;  // Stop if input is not a digit
        }
        total = total * 10 + (ch - '0');
    }

    cout << "\nNumber is: " << total << endl;

    return 0;
}

