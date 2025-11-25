#include<iostream>
using namespace std;

class CRect{
	public:
		double width;
		int height;
		int weight;
		
		void set(double wg){
			weight=wg;
		}
		
		void set(int w,int h){
			width=w;
			height=h;
		}
		
		void set(double wg ,int w,int h){
			weight=wg;
			width=w;
			height=h;
		}	
		
		void show(void){
			cout<<height<<endl<<width<<endl<<weight<<endl;
		}	
};
int main(void){
	CRect c;
	cin>>c.height>>c.width>>c.weight;
	c.set(c.weight,c.width,c.height);
	c.show();
}
