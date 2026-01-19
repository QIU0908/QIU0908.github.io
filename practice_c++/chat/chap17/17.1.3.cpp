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
};

class K2Mconverter:public DistConverter{
	public:
		K2Mconverter(double k):DistConverter(k){
			
			cout<<dist<<" kilo "<< convert(k)<<endl;
		}
		
		 double convert(double dist){
			return dist*=0.6214;
		}
};

class M2Kconverter:public DistConverter{
	public:
		M2Kconverter(double k):DistConverter(k){
			
			cout<<dist<<" mile "<< convert(k)<<endl;
		}
		 double convert(double dist){
			return dist*=1.6093;
		}
};

int main(void){
	K2Mconverter k1(10);
	M2Kconverter m1(6.214);
	
}