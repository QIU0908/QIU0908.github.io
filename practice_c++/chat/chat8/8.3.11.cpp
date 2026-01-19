#include<iostream>
using namespace std;

#define size 3
void find(int [][size]);

int main(void){
	int a[size][size]={{21,85,39},
					   {30,72,14},
					   {69,53,41}};
	find(a);
}
void find(int a[][size]){
	int min=a[0][0],p,k;
	cout<<"the matrix are "<<endl;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<a[i][j]<<" ";
			if(a[i][j]<min){
				min=a[i][j];
				p=i;
				k=j;
			}
		}
		cout<<endl;
	}
	cout<<"the minimun index = ["<<p<<"] ["<<k<<"]"<<endl;
	cout<<"tne minimum valumn = "<<min;
}