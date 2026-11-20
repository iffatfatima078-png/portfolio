#include <iostream>
using namespace std;

int main() {
    int height = 20;  // Total number of rows

    for (int i = 0; i < height; i++) { // Loop for each row

        for (int j = 0; j < height - i - 1; j++) // Print leading spaces
            cout << " ";

        for (int k = 0; k < (2 * i + 1); k++) // Print stars
            cout << "x";

        cout << endl; // Move to next line
    }

    return 0;
}

