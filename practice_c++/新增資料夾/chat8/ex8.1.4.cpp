#include<iostream>
using namespace std;

int main(void){

	int a[5]={2,5,6,7,4};
	int max=a[0],min=a[0];
	
	for(int i=0;i<=5;i++){
		if(a[i]>max)
			max=a[i];
		if(a[i]<min)
			min=a[i];
	}
	
	cout<<max<<endl<<min;	
	
}

