#include <iostream>
using namespace std;

int main() {
    int guests, chairs;
    long arrangements = 1;

    cout << "Enter number of guests: ";
    cin >> guests;

    cout << "Enter number of chairs: ";
    cin >> chairs;

    if (chairs > guests) {
        cout << "Error: More chairs than guests. Not allowed!" << endl;
        return 1;
    }

    // Calculate permutations: P(n, r) = n * (n - 1) * ... * (n - r + 1)
    for (int i = 0; i < chairs; i++) {
        arrangements *= (guests - i);
    }

    cout << "Number of possible arrangements: " << arrangements << endl;

    return 0;
}

