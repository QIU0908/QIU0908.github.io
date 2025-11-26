#include<iostream>
#include<cstring>
using namespace std;
class CWin{
	private:
		char id,title[2];
	public:
		CWin(char i='D',const char* text="DW"):id(i){
			strcpy(title,text);
		}
		~CWin(){
			cout<<"b"<<endl;
			system("pause");
		}
		void show(void){
			cout<<id<<": "<<title<<endl;
		}
		
};

int main(void){
	CWin a1('A',"you are a  ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");
	a1.show();
}