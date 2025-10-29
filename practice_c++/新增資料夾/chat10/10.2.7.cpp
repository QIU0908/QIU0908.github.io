#include<iostream>
using namespace std;

int main(void){
	int a[4][3]={{26,65,37},{10,32,47},{69,76,18},{40,74,32}};
	int max=**a;
	int min=**a;
	
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if( *(*(a+i)+j)>max )
			max=*(*(a+i)+j);
			if( *(*(a+i)+j)<min )
			min=*(*(a+i)+j);
		}
	}
	
	cout<<max<<"\t"<<min<<"\t"<<max-min;
	
}

