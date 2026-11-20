#include<iostream>
#include<conio.h>
using namespace std;
#define esc 27
class toolbooth
{
	unsigned int Cno;
	double tool;
	unsigned int tpayed;
public:
	toolbooth()
	{
		Cno = 0;
		tool = 0;
		tpayed = 0;
	}
	void payingCars()
	{
		Cno++;
		tool += 0.50;
		tpayed++;
		cout << "car" << Cno << "Passed";

	}
	void noPayCars()
	{
		Cno++;
		cout << "car" << Cno << "Passed" << endl;
	}
	void display()
	{
		cout << "\n\n Total Cars pass by :" << Cno;
		cout << "\n\n Total tool paid:" << tool << "cents" << endl;
		cout << "\n\nTotal cars that paid tool tax:" << tpayed << endl;
	}


};
int main()
{
	toolbooth t;
	char ch;
	cout << "Enter 1 to add car which payed tool tax!!" << endl;
	cout<<"Enter 1 to add car which payed tool tax!!" << endl;
	cout << "Enter Esc key to display total cars pass by and total tax payed !!" << endl;
	do
	{
		ch = getch();
		if (ch == '1')
			t.payingCars();
		else if (ch == '2')
			t.noPayCars();
		else
			cout << "Wrong Input" << endl;


	} while (ch == esc);
	t.display();
	return 0;
}

