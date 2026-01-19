#include <iostream>
using namespace std;

class CSale{
	private:
		char id;
		int quantity,price;
	public:
		CSale(char i,int q,int p){
			id=i;
			quantity=q;
			price=p;
		}
		
		void show(void){
			cout<<id<<"\t"<<quantity<<"\t"<<price<<"\t"<<quantity*price<<endl;
		}
		
		int all(void){
			return  quantity*price;
		}
		
		void compare(CSale *w){
    	if(this->all() > w->all())
        cout << this->id;
    	else
        cout << w->id<<endl;
		}
		
		char few(CSale &w){
			if(this->all() < w.all())
				return this->id;
			else
				return w.id;
		}
};

int main(void){
	CSale x1('a',10,34699);
	CSale x2('b',12,40400);
	
	x1.show();
	x2.show();
	x1.compare(&x2);
	cout<<x1.few(x2);
}