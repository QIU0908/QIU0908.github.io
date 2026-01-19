#include<iostream>
#include<string>
using namespace std;

struct inf{
	string name;
	string num;
};

union code {
	int spe;
	bool great;
};

int main(void){
	code code;
	inf inf;
	getline(cin,inf.name);
	cin.get();
	getline(cin,inf.num);
	int nee;
	cout<<"man (1) meil (2)";
	cin>>nee;
	
	if(nee==1){
		cin>>code.great;
	}else if(nee==2){
		cin>>code.spe;
	}else{
		cout<<"error";
	}
	
	cout<<inf.name<<endl<<inf.num<<endl;
	if(nee==1){
		cout<<code.great;
	}else if(nee==2){
		cout<<code.spe;
	}else{
		cout<<"error";
	}
	
	
}