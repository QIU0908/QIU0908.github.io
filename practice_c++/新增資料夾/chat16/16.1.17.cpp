#include<iostream>
#include<cstring>
using namespace std;
class Cwin{
	protected:
		char id;
	public:
		Cwin(char i='D'):id(i){
			cout<<"Cwin call out"<<endl;
		}
	
		Cwin(const Cwin & win){
			cout<<"Cwin copy got call out"<<endl;
			id=win.id;
			}
	
	
		~Cwin(){
			cout<<"Cwin destroy call out"<<endl;
			system("pause");
			}
};

class CTextwin :public Cwin{
	private:
		char text[20];
	public:
		CTextwin(char i,const char *tx):Cwin(i){
			cout<<"CTextwin call out"<<endl;
			
			strcpy(text,tx);
		}
		
		CTextwin(const CTextwin & tx):Cwin(tx){
			cout<<"CTextwin copy call out"<<endl;
			
			strcpy(text,tx.text);
		}
		
		
		~CTextwin(){
			
			cout<<"CTextwin destroy call out"<<endl;
			system("pause");
		}
		void show_member(){
			cout<<"window"<<id<<":";
			cout<<"text = "<<text<<endl;
		}
		void set_member(char i,const char *tx){
			id=i;
			strcpy(text,tx);
		}
};

int main(void){
	CTextwin tx1('A',"hello c++");
	CTextwin tx2(tx1);
	
	tx1.show_member();
	tx2.show_member();
	
	cout<<"after update tx1 member"<<endl;
	tx1.set_member('B',"welcome c++");
	
	tx1.show_member();
	tx2.show_member();
}