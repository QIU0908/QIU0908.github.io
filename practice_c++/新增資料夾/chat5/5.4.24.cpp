#include<iostream>
using namespace std;

int main(void){
	int i=2;
	bool num=1;
	while(num){
		if(i%3!=1){
				i++;
				continue;
			}else if(i%5!=3){
				i++;
				continue;
			}else if(i%7!=2){
				i++;
				continue;
			}else{
				num=0;				
			}	
	}
	cout<<i;
	return 0;
}