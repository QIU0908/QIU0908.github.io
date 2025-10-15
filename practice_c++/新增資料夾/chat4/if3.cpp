#include <iostream>
using namespace std;
int main(void){
	int a;
	cin >> a;
	if(a<0||a>100){
		cout<<"error";
	}else if(a>=90){
		cout<<"excelent";
	}else if(a>=60&&a<=89){
		cout<<"pass";
	}else {
		cout<<"no pass";
	
	}
	return 0 ;
}