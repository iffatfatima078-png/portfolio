#include<iostream>
using namespace std;

class time12 {
public:
    int hr12;
    int min12;
    bool isam;

    void display() {
        cout << hr12 << ":" << min12 << " ";
        if (isam)
            cout << "AM";
        else
            cout << "PM";
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

        t.hr12 = hr24;
        t.min12 = min24;

        // AM/PM logic
        if (hr24 >= 12)
            t.isam = false;
        else
            t.isam = true;

        // rounding seconds
        if (sec24 >= 30) {
            t.min12++;
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
    time24 t24(12, 59, 40);   // 24-hour time
    time12 t12 = t24;         // conversion

    t24.display();
    t12.display();

    return 0;
}
