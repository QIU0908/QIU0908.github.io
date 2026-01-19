#include<iostream>
using namespace std;

int main(void){
	for(int i=1;i<=100;i++){
		if(i%2!=0&&i%3!=0)
			continue;
		if(i%12==0)
			continue;
		cout<<i<<endl;
	}
}