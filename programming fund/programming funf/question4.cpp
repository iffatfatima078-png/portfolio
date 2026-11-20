#include <iostream>
using namespace std;

int main() {
    float num1, num2, result;
    char oper, again;

    do {
        // Input
        cout << "Enter first number, operator, second number: ";
        cin >> num1 >> oper >> num2;

        // Operation
        switch (oper) {
            case '+':
                result = num1 + num2;
                cout << "Answer = " << result << endl;
                break;
            case '-':
                result = num1 - num2;
                cout << "Answer = " << result << endl;
                break;
            case '*':
                result = num1 * num2;
                cout << "Answer = " << result << endl;
                break;
            case '/':
                if (num2 != 0)
                    result = num1 / num2;
                else {
                    cout << "Error: Division by zero!" << endl;
                    continue; // skip asking to continue
                }
                cout << "Answer = " << result << endl;
                break;
            default:
                cout << "Invalid operator!" << endl;
                continue; // skip asking to continue
        }

        // Ask to repeat
        cout << "Do another (y/n)? ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    return 0;
}

