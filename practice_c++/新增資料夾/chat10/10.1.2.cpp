#include<iostream>
#include <cstring>
using namespace std;


int main(void){
	const char *prt[3]={"apple","banana","grape"};
	for(int i=0;i<3;i++){
		cout<<prt[i]<<"\t";
		cout<<strlen(prt[i])<<endl;
		
	}
}