#include<iostream>
using namespace std;
class coord{
	private:
		double x,y;
	public:
		coord(double x=0,double y=0):x(x),y(y){
			
		}
		void show(){
			cout<<"("<<x<<" , "<<y<<")"<<endl;
		}
		
		void set(){
			
		}
		
		friend coord operator+(coord &y,coord &z);
		friend coord operator-(coord &y,coord &z);
};
	coord operator+(coord &y,coord &z){
			double a=y.x+z.x;
			double b=y.y+z.y;
			return coord(a,b);
		}
		
	coord operator-(coord &y,coord &z){
			double a=y.x-z.x;
			double b=y.y-z.y;
			return coord(a,b);
		}

int main(void){
	coord c0(1,1);
	coord c1(2,2);
	coord c2,c3;
	c2=c0+c1;
	c3=c0-c1;
	
	cout<<"c0=";
	c0.show();
	cout<<"c1=";
	c1.show();
	cout<<"c0+c1=";
	c2.show();
	cout<<"c0-c1=";
	c3.show();
}