#include <iostream>
using namespace std;

int main() {
    int ch, sub, qty;
    float total = 0;
    do {
        cout << "\n1. Pizza\n2. Burger\n4. Exit\nEnter choice: ";
        cin >> ch;

        if (ch == 1) {
            cout << "1. Pepperoni ($8)\n2. Veggie ($7)\n3. Chicken ($9)\nChoice: ";
            cin >> sub;
            cout << "Quantity: "; cin >> qty;
            if (sub == 1) total += 8 * qty;
            else if (sub == 2) total += 7 * qty;
            else if (sub == 3) total += 9 * qty;
            else cout << "Invalid!\n";
        }
        else if (ch == 2) {
            cout << "1. Classic ($5)\n2. Chicken ($6)\n3. Cheese ($7)\nChoice: ";
            cin >> sub;
            cout << "Quantity: "; cin >> qty;
            if (sub == 1) total += 5 * qty;
            else if (sub == 2) total += 6 * qty;
            else if (sub == 3) total += 7 * qty;
            else cout << "Invalid!\n";
        }
        else if (ch != 4)
            cout << "Invalid choice!\n";

    } while (ch != 4);

    cout << "\nTotal Bill: $" << total << endl;
    cout << "Thank you!\n";
    return 0;
}

