#include<iostream>
using namespace std;

class distance{
	int feet;
	float inchn;
	public:
		distance(int f,float i){
			feet=f;
			inchn=i;
		}
		distance(){
		}
		void getdata(){
			cin>>feet>>inchn;
		}
		void showdata(){
			cout<<feet<<"   "<<inchn;
		}
		distance add(distance);
		~distance(){
			cout<<" this is destrector";
		}
};
distance distance :: add(distance, d){
	distance t;
	t.feet=feet + d.feet;
	t.inchn= inchn + d.inchn;
	return t; 
}
int main (){
	distance d1(5,2.5);
	distance d2;
	distance d3=d2.add(d1);
	d3.showdata();
	return 0;
}
