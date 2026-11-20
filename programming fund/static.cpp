#include<iostream>
using namespace std;
class student{
	const int subject;
	int marks[5];
public:
     student (int s): subject(s){
	 }	
	 void getmarks(){
	 	cout<<"enter marks for"<<" "<<subject<<" "<<"subjects: \n";
	 	for(int i=0; i=subject; i++){
	 		cin>>marks[i];
		 }
	 }
	 void show(){
	 	int sum=0;
	 	for(int i=0; i<subject; i++)
	 	sum+=marks[i];
	 	cout<<"average: "<<sum/(float)subject<<endl;
	 }
};
int main(){
	int n;
	cout<<"enter number of subject: ";
	cin>>n;
	student s(n);
	s.getmarks();
	s.show();
	return 0;
	
}

