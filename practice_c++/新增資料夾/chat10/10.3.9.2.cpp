#include<iostream>
using namespace std;

int main(void){
	int *a;
	a=new int[2];
	for(int i=0;i<2;i++){
		cout<<"input a num ";
		cin>>*(a+i);
	}
	cout<<endl;
	cout<<*(a+0)<<"*"<<*(a+1)<<"="<<*(a+0) * *(a+1);
	delete[]a;
	a=nullptr;
	return 0;
}