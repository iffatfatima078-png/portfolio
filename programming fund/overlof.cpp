
#include<iostream>
using namespace std;

class test{
    int num;
public:
    test() {}   // default constructor

    test(int n){
        num = n;
    }

    test operator +(test t2){
        test temp;
        temp.num = num + t2.num;
        return temp;
    }

    void display(){
        cout << "value : " << num << endl;
    }
};

int main(){
    test t1(5);
    test t2(10);
    test t3;

    t3 = t1 + t2;
    t3.display();

    return 0;
}
