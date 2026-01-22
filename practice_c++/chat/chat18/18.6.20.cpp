#include<iostream>
namespace name1{
	int var=5;
}
using namespace std;
int main(void){
	int var=10;
	cout<<name1::var;
	return 0;
}