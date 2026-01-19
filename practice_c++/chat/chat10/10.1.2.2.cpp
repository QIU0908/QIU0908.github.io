#include<iostream>

using namespace std;

int countLen(const char* );

int main(void){
	const char* prt[3]={"apple","banana","grape"};
	for(int i=0;i<3;i++){
		cout<<*(prt+i)<<"\t"<<countLen(prt[i])<<endl;
	}
}

int countLen(const char* str) {
    int len = 0;
    while (*(str+len)!= '\0') len++;
    return len;
}
