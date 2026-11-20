#include<iostream>
using namespace std;

class a{
	public:
		void show(){
			cout<<"show a"<<endl;
		}
};
class b{
	public:
		void show(){
			cout<<"show b"<<endl;
		}
};
class c: public a, public b{
	public:
		void show(){
			a::show();
			b::show();
		}
};
int main(){
	c obj;
	obj.show();
	return 0;
}
