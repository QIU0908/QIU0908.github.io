#include<iostream>
namespace name1{
	int var=5;
}
using namespace std;
int main(void){
	int var=10;
		{
			using namespace name1;
		cout<<name1::var<<endl;
		}
	

	cout <<"var = "<<var<< endl;
	return 0;                 
}    