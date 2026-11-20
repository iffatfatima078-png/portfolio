#include<iostream>
#include<cstring>
#include<conio.h>
using namespace std;

int main() {
	char userstore[20] = "ABC@gmail.com";
	char userinput[20];
	char pwdstore[20] = "abc@123";
	char pwdinput[20];
	char ch;
	int i = 0;

	cout << "Enter email:" << endl;
	cin >> userinput;

	cout << "Enter password" << endl;

	// if you'll enter strcmpi it'll not run in dev
	while (1) {
		ch = _getch();

		if (ch == 13)
			break;
		if (ch == 8) {
			cout << "\b";
			cout << " ";
			cout << "\b";
			i--;
		}
		else {

			cout << "*";
			pwdinput[i++] = ch;
		}
	}
	pwdinput[i] = '\0';
	cout << pwdinput;

	if (_strcmpi(userstore, userinput) == 0 && strcmp(pwdstore, pwdinput) == 0) {
		cout << "\nLogin successfully" << endl;

	}
	else {
		cout << "\nEither username or password id wrong ";
	}


	return 0;
}

