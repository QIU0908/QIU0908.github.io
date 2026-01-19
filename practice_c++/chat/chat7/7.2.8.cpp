#include<iostream>
using namespace std;

void proverb();
void proverb(int);


int main(void){
	int i;
	cin>>i;
	proverb();
	proverb(i);
}

void proverb(){
	cout<<"two head are better than one"<<endl;
	return ;
}
void proverb(int n){
	for(int i=1;i<=n;i++){
		cout<<"two head are better than one"<<endl;
	}
	return ;
}