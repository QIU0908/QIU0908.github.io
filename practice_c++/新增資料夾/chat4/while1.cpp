#include<iostream>
using namespace std;
int main(void){
	int num ,i=1,sum=0;
	cin >> num;
	
	while(i<=num){
		sum+=i;
		i++;
	} 
	cout<<sum;
	return 0;
}