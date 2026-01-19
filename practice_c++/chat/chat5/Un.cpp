#include<iostream>
using namespace std;

int main(void){
	int i=1,a=0;
	while(i<200){
		i++;
		if(i%2==0){
			a+=i;
		}
}
cout<<a;
return 0;
}