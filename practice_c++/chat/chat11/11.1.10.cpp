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
	for(a=Monday;a<=Sunday;a=static_cast<day>(a+1)){
		cout<<b[a]<<endl;
	}
   
}


