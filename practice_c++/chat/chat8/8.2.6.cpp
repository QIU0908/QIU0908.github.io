#include<iostream>
using namespace std;

int main (void){
	int A[2][3]={{51,5,6},{3,8,25}};
	int b=100,k,l;
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			if(A[i][j]<b){
				b=A[i][j];
				k=i;
				l=j;
			}
			
		}
	}
	cout<<"the Minimum inderx if ["<<k<<"] ["<<l<<"] ,value is "<<b;
}