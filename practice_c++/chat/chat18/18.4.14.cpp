#include<iostream>
#include<fstream>
using namespace std;

int main(void){
	ifstream ifile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\butchartgarden.txt",ios::in);
	
	if(ifile.is_open()){
	char ch;
	int z=0;
	
	while(ifile.get(ch)){
		if(ch=='a'||ch=='A')
		z++;
		if(ch=='e'||ch=='E')
		z++;
		if(ch=='i'||ch=='I')
		z++;
		if(ch=='o'||ch=='O')
		z++;
		if(ch=='u'||ch=='U')
		z++;
	}
		cout<<z;
		
	}
	
}