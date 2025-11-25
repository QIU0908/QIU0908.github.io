#include<iostream>
using namespace std;
 
 class CBodyfit{
 	private:
 		char id;
 		double height;
 		double weight;
 	public:
 		CBodyfit(char i,double h,double w){
 			id=i;
 			height=h;
 			weight=w;
 			cout<<"use\n";
		 }
		 
		void show(void){
			cout<<id<<height<<weight<<"bmi "<<weight/(height*height/10000.)<<endl;
		}
 };
 
 int main(void){
 	CBodyfit cb1('A',160.5,45.5);
 	CBodyfit cb2('b',180.3,78.2);
 	cb1.show();
 	cb2.show();
 }