#include<iostream>
using namespace std;

class CTemp{
	public:
		float C;
		float F;
	float Ctof(void){
		return (C/0.37);
	}
};

int main(void){
	CTemp x;
	cin>>x.C ;
	cout<<x.Ctof();
}