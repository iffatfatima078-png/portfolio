#include<iostream>
using namespace std;

class test{
	int value;
public:
	test(){
		value=0;
		cout<<"default constructor called!"<<endl;
	}
	test(int r){
		int roll=r;
		cout<<roll<<endl;
	}
void show() {
        cout<<"value ="<<value<<endl;
}
~test(){
	cout<<"destructor calles!"<<endl;
}	
};
int main(){
	test obj1;
	test obj2(23);
	obj1.show();
	obj2.show();
	return 0;
}


