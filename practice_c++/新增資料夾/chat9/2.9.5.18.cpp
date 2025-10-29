#include<iostream>

using namespace std;

#define lineMax 20

int main(void){
	char santance[lineMax];
	cin.getline(santance, lineMax);
	int n=0;
	while(*(santance+n)!='\0'){
		if(*(santance+n)==' ')
		*(santance+n)='*';
		cout<<*(santance+n);
		n++;
	}
	
}