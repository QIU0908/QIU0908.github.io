#include<iostream>
using namespace std;

class DistConverter{
	protected:
		double dist;
	public:	
		DistConverter(double k=1):dist(k){}
		virtual double convert(double dist){
			return dist;
		}
		void virtual show(void){
			cout<< "0"<<endl;
		}
};

class K2Mconverter:public DistConverter{
	public:
		K2Mconverter(double k):DistConverter(k){
			
		
		}
		
		 double convert(double dist){
			return dist*=0.6214;
		}
		
		void virtual show(void){
				cout<<dist<<" kilo "<< convert(dist)<<endl;
		}
		
};

class M2Kconverter:public DistConverter{
	public:
		M2Kconverter(double k):DistConverter(k){
		}
		
		double convert(double dist){
			return dist*=1.6093;
		}
		
		void virtual show(void){
				cout<<dist<<" mile "<< convert(dist)<<endl;
		}
};

int main(void){
	K2Mconverter k1(10);
	M2Kconverter m1(6.214);
	
	K2Mconverter *prt = &k1;
	prt->show();
	
	M2Kconverter *prt1 = &m1;
	prt1->show();
	
	
}