#include<iostream>
using namespace std;
int main(void){
	int i;
	bool isp=0;
	for(int i=2;i<=100;i++){
		if(45%i!=0){	
			continue;
		}	
		
	
		
		for(int j=2;j<i;j++){
			if(i%j==0){
				isp=1;
				break;
			}
			
		}
		
		
		if(isp)//when isp==1 then jump over the cout;
		continue; 
		cout<<i<<endl;
		
		}
		return 0;
	}