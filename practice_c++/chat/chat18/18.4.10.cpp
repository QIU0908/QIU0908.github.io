#include<fstream>
#include<iostream>
#include<string>
using namespace std;

int main(void){
	ofstream ofile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\bbb.txt",ios::out);
	
	if(ofile.is_open()){
		string a;
		cout<<"pleace input a stance ."<<endl;
		getline(cin, a);
		ofile <<a<<endl;
		cout<<"secce"<<endl;
	}
	else 
		cout<<"error"<<endl;
		
	ofile.close();
	return 0;
}