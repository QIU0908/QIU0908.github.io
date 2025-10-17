#include<iostream>
using namespace std;

int main(void){
float b=0;
float a[5];
for(int i=0;i<5;i++){
	cout<<"input number #"<<i+1<<": ";
	cin>>a[i];
	b=b+a[i];
}
cout<<"Average of all is "<< b/5;

}