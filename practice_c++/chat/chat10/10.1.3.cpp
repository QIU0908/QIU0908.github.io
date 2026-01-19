#include<iostream>
#include <string>
using namespace std;

int main(int argc,char*argv[]){
	double a = stod(argv[1]);
	int b = stoi(argv[2]);
	double ans=1;
	for(int i=0;i<b;i++){
		ans*=a;
	}
	cout<<"a^b= "<<ans;
}