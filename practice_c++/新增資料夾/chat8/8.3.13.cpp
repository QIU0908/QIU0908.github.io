#include<iostream>
using namespace std;

#define raw 4
#define column 3

void find(int [raw][column]);

int main(void){
	int a[raw][column]={{26,15,72},{10,36,47},
						{65,76,38},{40,49,32}};
						
	find(a);
	
}

void find(int a[raw][column]){
	int max=a[0][0],min=a[0][0];
	cout<<"elements in array:"<<endl;
	for(int i=0;i<raw;i++){
		for(int j=0;j<column;j++){
			cout<<a[i][j]<<" ";
			if(a[i][j]>max)
			max=a[i][j];
			if(a[i][j]<min)
			min=a[i][j];
		}cout<<endl;
	}
	cout<<"maximum="<<max<<endl<<"minimum="<<min;
}