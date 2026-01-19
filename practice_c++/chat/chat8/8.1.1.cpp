#include<iostream>
using namespace std;

int main(void){
	int A[5]={76,75,30,17,6},max,min;
	max=A[0];
	min=A[0];
	for(int i=0;i<=4;i++){
		if(A[i]>max)
			max=A[i];
		if(A[i]<min)
			min=A[i];
		cout<<A[i]<<endl;
	}
	cout<<"max ="<<max<<endl<<"min ="<<min<<endl;
	return 0;
}