#include<iostream>
#include <string>
using namespace std;

int main(int argc,char*argv[]){
	int a = stoi(argv[1]);
	if(a>0&&a%2==0){
		cout<<"is 2,4,6";
	}else if(a==0){
		cout<<"is 0";
	}else{
		cout<<"is 1,3,5";
	}
}