#include<iosteam>
using namespace std;

int main(void){
	int i=1,num=1,a=0;
	while(i<20){
		num++;
		if(num%2==0)
		cout<<num;
		a=a+num*num;
	}
	cout<<a;
	
	return 0
}