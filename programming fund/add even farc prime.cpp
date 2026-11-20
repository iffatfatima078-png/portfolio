#include <iostream>
using namespace std;

void menu();
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
bool isPrime(int n);
bool isEven(int n);

int main() {
    int choice, n, a, b;

    do {
        menu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 6)
            break;

        if (choice >= 1 && choice <= 3) {
            cout << "Enter two numbers: ";
            cin >> a >> b;
        } else {
            cout << "Enter one number: ";
            cin >> n;
        }

        switch (choice) {
            case 1:
                cout << "Sum = " << add(a, b) << endl;
                break;

            case 2:
                cout << "Difference = " << sub(a, b) << endl;
                break;

            case 3:
                cout << "Product = " << mul(a, b) << endl;
                break;

            case 4:
                cout << (isPrime(n) ? "Prime\n" : "Not Prime\n");
                break;

            case 5:
                cout << (isEven(n) ? "Even\n" : "Odd\n");
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

void menu() {
    cout << "\n--- MENU ---\n";
    cout << "1. Add\n";
    cout << "2. Subtract\n";
    cout << "3. Multiply\n";
    cout << "4. Check Prime\n";
    cout << "5. Check Even/Odd\n";
    cout << "6. Exit\n";
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0) return false;
    return true;
}

bool isEven(int n) { return n % 2 == 0; }

