#include <iostream>
 using namespace std;
 
 int main(void){
 	int num=1;
 	for(int i=1;i<=5;i++){
 		for(int j=1;j<=i;j++){
 			cout<<num;
		}
			cout<<endl;
		num++;
	 }
	 return 0;
 }