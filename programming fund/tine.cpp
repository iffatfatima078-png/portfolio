#include<iostream>
using namespace std;

class time12 {
public:
    int hr12;
    int min12;
    bool isam;

    void display() {
        cout << hr12 << ":";
        
        // formatting for minutes (e.g., 1:05 instead of 1:5)
        if (min12 < 10)
            cout << "0";
        cout << min12 << " ";

        if (isam)
            cout << "AM";
        else
            cout << "PM";

        cout << endl;
    }
};

class time24 {
public:
    int hr24;
    int min24;
    int sec24;

    time24(int h, int m, int s) {
        hr24 = h;
        min24 = m;
        sec24 = s;
    }

    operator time12() {
        time12 t;

        // copy hour & minute
        t.hr12 = hr24;
        t.min12 = min24;

        // AM / PM
        if (hr24 >= 12)
            t.isam = false; // PM
        else
            t.isam = true;  // AM

        // round seconds
        if (sec24 >= 30) {
            t.min12++;
        }

        // handle minute overflow
        if (t.min12 == 60) {
            t.min12 = 0;
            t.hr12++;
        }

        // convert to 12-hour format
        if (t.hr12 > 12) {
            t.hr12 -= 12;
        }

        if (t.hr12 == 0) {
            t.hr12 = 12;
        }

        return t;
    }

    void display() {
        cout << hr24 << ":" << min24 << ":" << sec24 << endl;
    }
};

int main() {
    time24 t24(14, 35, 40);   // test value
    time12 t12 = t24;         // conversion

    cout << "24-hour format: ";
    t24.display();

    cout << "12-hour format: ";
    t12.display();

    return 0;
}
