#include<iostream>
using namespace std;

#define size 10
void find(int []);

int main(void){
	int A[size]={51,36,88,74,45,3,98,71,63,55};
	find(A);
}

void find(int a[]){
	int j=0,k=0;
	cout<<"A[]=";
	for(int i=0;i<size;i++){
		cout<<a[i]<<" ";
		if(a[i]%2==0)
		k+=1;
		if(a[i]%2!=0)
		j+=1;
	}
	cout<<endl;
	cout<<"odd "<<j<<" even "<<k;
}