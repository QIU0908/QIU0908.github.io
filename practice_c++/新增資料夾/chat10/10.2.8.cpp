#include<iostream>
using namespace std;

int main(void){
	int arr[2][4]={{1,2,3,4,},{5,6,7,8}};
	cout<<arr[0][0]<<endl;
	cout<<arr<<endl;
	cout<<arr[0]<<"\t"<<arr[1]<<endl;
	cout<<arr+1<<endl;
	cout<<*(arr+0)<<"\t"<<*(arr+1) <<endl;
	cout<<*(arr+1)+0<<"\t"<<*(arr+1)+1<<"\t"<<*(arr+1)+2<<"\t"<<*(arr+1)+3<<"\t"<<endl;
	cout<<*(*(arr+1)+0)<<"\t"<<*(*(arr+1)+1)<<"\t"<<*(*(arr+1)+2)<<"\t"<<*(*(arr+1)+3)<<"\t"<<endl;
}