#include<iostream>
using namespace std;

#define size 5
void find(int []);

int main(void){
	int a[size]={48,75,30,17,62};
	find(a);
}

void find(int a[]){
	int max=a[0],min=a[0];
	int maxIndex,minIndex;
	cout<<"matrix is ";
	for(int i=0;i<size;i++){
		cout<<a[i]<<" ";
		if(a[i]>max){
			max=a[i];
			maxIndex=i;
		}
		if(a[i]<min){
			min=a[i];
			minIndex=i;
		}
			
	}
	cout<<endl;
	cout<<"the maximum index is "<<maxIndex<<endl;;
	cout<<"the mimimum index is "<<minIndex<<endl;;
	cout<<"the max-min "<<max-min;	
	return ;	
}