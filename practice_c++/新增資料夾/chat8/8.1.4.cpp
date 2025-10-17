#include<iostream>
using namespace std;

int main(void){
	int a[100],i=0;
	float u=0;
	bool finger=0;
	cout<<"enter -1 stopping input"<<endl;
	do{
		cout<<"input score:";
		cin>>a[i];
		if(a[i]==-1)
			finger=1;
		else{
			u+=a[i];
			i++;
			}
		}while(!finger&&i<100);
		
	cout<<"Average of all is "<<u/i;
		
	
}