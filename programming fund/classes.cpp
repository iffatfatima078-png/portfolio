#include<iostream>
using namespace std;

class x{
	int a=5;
	friend class y;
};
class y{
	public:
		void show(x obj){
	cout <<obj.a<<endl;
}
};
int main(){
	x obj1;
	y m;
	m.show(obj1);
	return 0;
}
