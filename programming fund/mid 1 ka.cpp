#include <iostream>
#include <cctype>  // for isupper, islower, isdigit
#include <string>
using namespace std;

int main() {
    string password;
    bool hasUpper = false, hasLower = false, hasDigit = false;

    cout << "Enter password: ";
    cin >> password;

    // Check password length
    if (password.length() < 6) {
        cout << "Password must be at least 6 characters long.\n";
        return 0;
    }

    // Check each character
    for (int i = 0; i < password.length(); i++) {
        if (isupper(password[i])) hasUpper = true;
        if (islower(password[i])) hasLower = true;
        if (isdigit(password[i])) hasDigit = true;
    }

    // Check all conditions
    if (hasUpper && hasLower && hasDigit)
        cout << "Password is valid!\n";
    else {
        cout << "Invalid password! It must contain:\n";
        if (!hasUpper) cout << "- At least one uppercase letter\n";
        if (!hasLower) cout << "- At least one lowercase letter\n";
        if (!hasDigit) cout << "- At least one digit\n";
    }

    return 0;
}

