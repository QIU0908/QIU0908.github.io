#include <iostream>
#include <string>
using namespace std;

class CSale{
	private:
		string id;
		int quantity,price;
		void set_data(string i,int q,int p){
			id=i;
			quantity=q;
			price=p;	
		}
	public:
		
	};
	
	
	
	
int main(void){
	CSale c1,c2;
	c1.set_data("ix m60 \t",3,638);
	c2.set_data("x5 m sport",5,392);
	
}