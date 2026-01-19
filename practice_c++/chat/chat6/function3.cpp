#include<iostream>
using namespace std;

void fact(int);
void sum(int);

int main(void) {
    char ch;  // 判斷是否停止
    do {
        int a;
        cout << "put in a int"<<endl;
        cin >> a;
        fact(a);
        sum(a);
        cout << "coutinum push a if not push s"<<endl;
        cin >> ch;
    } while (ch != 's' && ch != 'S'); 
    cout << "end" << endl;
    return 0;
}

void fact(int a){
	int ans=1,i=1;
	for(i;i<=a;i++){
		ans*=i;	
	}
	cout<<"1*2...*"<<a<<"="<<ans<<endl;
	return ;
}

void sum(int a){
	int ans=0,i=1;
	for(i;i<=a;i++){
		ans+=i;
	}
	cout<<"1+2+...+"<<a<<"="<<ans<<endl;
	return ;
}