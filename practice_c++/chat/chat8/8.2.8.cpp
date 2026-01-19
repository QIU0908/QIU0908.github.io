#include<iostream>
using namespace std;

int main(void){
	int a[3][3]={{3,2,1,},
				{5,6,7},
				{2,4,6}};
	int b[3][2]=  {{2,3},	
				{3,4},
				{6,2}};
	int c[3][2]={0};
	
for(int i=0;i<3;i++){
	for(int j=0;j<2;j++){
		for(int k=0;k<3;k++)
		c[i][j]+=a[i][k]*b[k][j];
	}
}
for(int i=0;i<3;i++){
	for(int j=0;j<2;j++){
		cout<<c[i][j]<<"\t";
	}
	cout<<endl;
	}
	
	
}