#include<iostream>
using namespace std;

struct student{
	char name[30];
	int rollno;
	int marks[3];
	float Avg;
};
int main(){
	student s[3];
	float totalAvg=0;
	
	for(int i=0; i<3; i++){
	cout<<"Enter name"<<(i+1)<<":";
	cin>>s[i].name;
	cout<<"Enter the rollno"<<(i+1)<<":";
	cin>>s[i].rollno;
	
	int sum=0;
	cout<<"enter 3 subject marks: ";
	for(int j=0; j<3; j++){
	
	cin>>s[i].marks[j];
	sum+=s[i].marks[j];
}
	
	

    s[i].Avg=sum/3.0;
    totalAvg+=s[i].Avg;
}
    cout<<"\nName\tRollno\tmarks\taverage\n";
    cout<<"..................................\n";
    for(int i=0; i<3; i++){
    cout<<s[i].name<<"\t"
   <<s[i].rollno<<"\t"
    <<s[i].marks[0]<<","<<s[i].marks[1]<<","<<s[i].marks[2]<<"\t"
    <<s[i].Avg<<"\n";
	}
	cout<<"totalAvg="<<totalAvg/3.0<<endl;
	return 0;
	}
    
