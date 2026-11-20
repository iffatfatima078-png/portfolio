#include<iostream>
using namespace std;

class Distance {
    int meter;

public:
    class error {
    public:
        int value;
        error(int v) {
            value = v;
        }
    };

    Distance(int m) {
        meter = 10000;   // initialize first (example balance)

        if (m > meter)
            throw error(m);

        meter -= m;
    }

    void display() {
        cout << "withdraw successfully " << meter << endl;
    }
};

int main() {
    try {
        Distance d1(200);
        d1.display();

        Distance d2(60000);
        d2.display();
    }
    catch (Distance::error e) {
        cout << "not possible " << e.value << endl;
    }
    catch (...) {
        cout << "default" << endl;
    }

    return 0;
}
