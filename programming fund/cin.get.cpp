#include<iostream>
using namespace std;

struct student{
	int x;
	int y;
};

int main(){
	student s1={1,2};
	student s2={1,2};
	student s3;
	s3.x=s1.x+s2.x;
	s3.y=s2.y-s2.x;
	cout<<s3.x<<s3.y<<endl;
	
	return 0;
}
