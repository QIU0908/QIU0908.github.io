#include<iostream>
#include<string>
using namespace std;

enum day{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
};

int main() {
	string b[7]{
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
	};
	day a;
	int x;
	cin>>x;
	a=static_cast<day>(x-1);
	cout<<b[a]<<endl;
	
   
}


