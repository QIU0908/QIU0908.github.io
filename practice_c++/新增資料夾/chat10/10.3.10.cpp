#include<iostream>
#include<cstring>
using namespace std;

int main(void){
	const char *src1="Rome was not built in a day";
	const char *src2="knowledge is power";
	
	char *ptr1 = new char[strlen(src1)+1];
	char *ptr2 = new char[strlen(src2)+1];
	
	strcpy(ptr1,src1);
	strcpy(ptr2,src2);
	
	
	cout<<ptr1<<endl<<ptr2<<endl;
	
	char *temp=ptr1;
	ptr1=ptr2;
	ptr2=temp;
	cout<<ptr1<<endl<<ptr2;
	
	delete[]ptr1;
	delete[]ptr2;
	
	ptr1=nullptr;
	ptr2=nullptr;
	
	
}