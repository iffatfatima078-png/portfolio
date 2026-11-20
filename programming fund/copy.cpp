#include<iostream>
using namespace std;

class Distance{
    int feet;
    float inch;

public:
    Distance(int f, float i){
        feet = f;
        inch = i;
    }

    Distance(){
        feet = 0;
        inch = 0;
    }
    void getdata(){
    	cin>>feet>>inch;
	}

    void showdata(){
        cout << feet << "  " << inch;
    }

    Distance add(Distance);

    ~Distance(){
        cout << " this is destructor"<<endl;
    }
};

Distance Distance::add(Distance d){
    Distance t;
    t.feet = feet + d.feet;
    t.inch = inch + d.inch;
    return t;
}

int main(){
    Distance d1(5, 2.5);
    Distance d2;
    d2.getdata();
    Distance d3 = d2.add(d1);
    d3.showdata();
    return 0;
}

