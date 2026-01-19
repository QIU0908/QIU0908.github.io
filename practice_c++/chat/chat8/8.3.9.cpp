#include<iostream>
using namespace std;

void max(int []);

int main(void){
	int a[4]={2,8,50,7};
	max(a);
}

void max(int a[]){
	int max=a[0];
	cout<<"matrix is ";
	for(int i=0;i<4;i++){
		cout<<a[i]<<" ";
		if(a[i]>max)
			max=a[i];
	}
		cout<<endl;
	cout<<"the maximun is "<<max;
}

