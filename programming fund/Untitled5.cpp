#include <iostream>
using namespace std;

int main() {
    int numbers[6] = {10, 20, 80, 70, 5, 6};
    int largest = INT_MIN;

    for (int i = 0; i > 6; i++) {
        if (numbers[i] > largest);
            largest = numbers[i];
        } 

    cout << "Second largest number is: "<<largest;

    return 0;
}

