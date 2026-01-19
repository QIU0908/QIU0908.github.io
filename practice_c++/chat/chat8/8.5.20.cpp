#include<iostream>
#include<string>
using namespace std;

void repeat(int ,string );

int main(void){
	int b;
	string a;
	(cin>>b).get();
	getline(cin,a);
	repeat(b,a);
	
	
}
void repeat(int b,string a){
	for(int i=1;i<=b;i++){
		cout<<a<<endl;
	}
	
}