#include<iostream>
using namespace std;

class AbstractBMI{
	protected:
		double height ,weight;
	public:
		AbstractBMI(double h=0, double w=0) : height(h), weight(w) {}
		  
		virtual double calculateBMI()=0;	
		
		 void show(void){
			cout<<"height = "<<height<<" weight = "<<weight<<" BMI ="<<calculateBMI()<<endl;
		}
};

class KiloBMI:public AbstractBMI{
	public:
		KiloBMI(double h,double w):AbstractBMI(h,w){
		}
		
		virtual double calculateBMI(){
			return weight/(height/100*height/100);
		}
		
};

class LbBMI:public AbstractBMI{
	public:
		LbBMI(double h,double w):AbstractBMI(h,w){
		}
		
		virtual double calculateBMI(){
			return (weight / (height * height)) * 703;
		}
		
};

int main(void){
	KiloBMI KBMI(170,65);
	LbBMI	LBMI(70,150);
	
	KBMI.show();
	LBMI.show();
}