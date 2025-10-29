#include<iostream>
using namespace std;

int main(void){
	int a[2][3]={{2,2,6},{3,2,8}};
	int b[2][3]={{5,2,3},{3,3,7}};
	
	for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			*(*(a+i)+j) += *(*(b+i)+j);
			cout<<*(*(a+i)+j)<<"\t";
		}cout<<endl;
	}
}