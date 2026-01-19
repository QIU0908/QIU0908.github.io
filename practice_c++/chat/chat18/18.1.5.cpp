#include<iostream>
using namespace std;

int fact(int n){		
		int a=1;
			for(int i=1;i<=n;i++){
				a*=i;
			}
			return a;
}

int main(void){
	for(int i=-2;i<=15;i++){
	try{
		if(i<0)
			throw "argument out of bound";
		else if(i>12)
			throw "number too large";
		else{
			cout << "fact(" << i << ") = " << fact(i) << endl;	
		}
	 		
	}
	
	catch(const char* str){
		cout<<i<<" "<<str<<endl;
	}
	}
}