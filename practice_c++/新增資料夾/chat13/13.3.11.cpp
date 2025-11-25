#include<iostream>
using namespace std;
 
#define p 5
 
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
			cout<<id<<"\t"<<height<<"\t"<<weight<<"\t"<<"bmi\t"<<weight/(height*height/10000.)<<endl;
		}
		
		double bmi(void){
			return weight/(height*height/10000.);
		}
		
		static void compare(CBodyfit w[]){
 			int min=w[0].bmi(),iw;
 			for(int i=1;i<p;i++){
 				if(w[i].bmi()<min){
 					min=w[i].bmi();
 					iw=i;
		 			}
	 		}cout<<w[iw].id<<"\t"<<min;
 		}	
};
 

 int main(void){
 	
 	CBodyfit cb[p]{
 		CBodyfit('a',160.9,50.8),
 		CBodyfit('b',180.3,78.2),
 		CBodyfit('c',160.5,45.5),
 		CBodyfit('d',152.7,65.6),
 		CBodyfit('e',192.7,95.1),	
	 }; 
	 CBodyfit::compare(cb);
 }