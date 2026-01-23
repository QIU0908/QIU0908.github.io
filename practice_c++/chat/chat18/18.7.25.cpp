#include<iostream>
using namespace std;

#define SIZE 5

int main(void){	
	#ifdef SIZE
		int arr[SIZE];
		#if SIZE>10
			for(int i=0;i<SIZE;i++){
				arr[i]=i+arr[i-1];
				cout<<arr[i]<<endl;
			}
		#else 
			for(int i=0;i<SIZE;i++){
				arr[i]=i*i;
				cout<<arr[i]<<endl;
			}
		#endif
	#else
		cout<<"SIZE are not define"<<endl;
	#endif	
}