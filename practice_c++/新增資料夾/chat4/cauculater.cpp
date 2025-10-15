#include <iostream>
#include <cmath> 
using namespace std;
int main(void){
double a,b;
char c;
int d;
cin >> a >> c >>b;

switch(c){
	case '*' : cout<<a<<"*"<<b<<"="<<a*b; break;
	case '+' : cout<<a<<"+"<<b<<"="<<a+b; break;
	case '-' : cout<<a<<"-"<<b<<"="<<a-b; break;
	case '/' :  b != 0?cout<<a<<"/"<<b<<"="<<a/b:cout << "Division by zero!"; 
			break;
	case '%' : b != 0?cout << a << "%" << b << "=" << fmod(a, b):cout << "Division by zero!";
            break;
	default:cout<<"error"; 	
}

return 0;

}