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

string datliy(day );

int main() {
	
	day a;
	for(a=Monday;a<=Sunday;a=static_cast<day>(a+1)){
		cout<<datliy(a)<<endl;
	}
   
}
string datliy(day b){
	switch(b){
		case Monday :return "Monday";
		case Tuesday :return "Tuesday";
		case Wednesday :return "Wednesday";
		case Thursday :return "Thursday";
		case Friday :return "Friday";
		case Saturday :return "Saturday";
		case Sunday :return "Sunday";
		default :return "error";
	}
}


