#include<iostream>

using namespace std;

#ifndef MAX_SIZE
#define MAX_SIZE 10
#endif

int main(void){
	
	
	
	double arr[MAX_SIZE];
	
	for(int i=0;i<MAX_SIZE;i++){
		arr[i]=i*i;
		cout<<arr[i]<<endl;
	}
	
}