#include<iostream>
#include<cstring>
using namespace std;
struct Games{
	char Name[80];
	char Rating;
	bool played;
	long NumberOfKills;
}
 unreal,Blizzard[3];
typedef Games*Gamesptr;

int main()
{
	unreal.Rating=1;
	strcpy(unreal.Name,"unreal");
	unreal.played=true;
	unreal.NumberOfKills=100;
	
	Games Quake;
	Quake.Rating=2;
	strcpy(Quake.Name,"Quake");
	Quake.played=true;
	Quake.NumberOfKills=100;
	cout<<"\n Quake Rating is: "<<Quake.Rating;
	Gamesptr gptr;
	gptr=&Quake;
	
	gptr->Rating=1;
	strcpy(gptr->Name,"Warcraft2");
	gptr->played=false;
	gptr->NumberOfKills=0;
	
	cout<<"\n Quake Rating is:"<<Quake.Rating;
	
	return 0;
}

