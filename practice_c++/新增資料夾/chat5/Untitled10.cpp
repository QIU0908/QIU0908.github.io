#include<iostream>
using namespace std;
int main(void){
	int road=3500;
	for(int day=1;day<10000000000;day++){
		
		road/=2;
		
		if(road<3){
			cout<< "day is "<<day ;
			break;
			
		}
		
	}
	
	
	return 0;
}