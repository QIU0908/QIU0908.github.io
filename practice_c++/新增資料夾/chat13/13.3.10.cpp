#include <iostream>
#include <string>
using namespace std;

class CSale{
	private:
		string id;
		int quantity,price;
	public:
		
		
		void show(void){
			cout<<id<<"\t"<<quantity<<"\t"<<price<<"\t"<<quantity*price<<endl;
		}
		
		friend void set_data(CSale &,string ,int ,int );
	};
	
	void set_data(CSale &w,string i,int q,int p){
			w.id=i;
			w.quantity=q;
			w.price=p;	
		}
	
	
int main(void){
	CSale c1,c2;
	set_data(c1,"ix m60 \t",3,638);
	set_data(c2,"x5 m sport",5,392);
	c1.show();
	c2.show();
}