#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char name[50];

    cout << "Enter a word or number: ";
    cin >> name;   // Works for both text and numbers

    int i = 0;
    int j = strlen(name) - 1;
    bool p = true;

    while (i < j) {
        if (name[i] != name[j]) {
            p = false;
            break;
        }
        i++;
        j--;
    }

    if (p)
        cout << "Palindrome" << endl;
    else
        cout << "Not palindrome" << endl;

    return 0;
}

