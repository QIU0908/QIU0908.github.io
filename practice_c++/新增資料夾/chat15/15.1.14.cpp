#include<iostream>
using namespace std;
class CTime{
	private:
		int hour,min;
		double sec;
	public:
		CTime(int h=0,int m=0,double s=0):hour(h),min(m),sec(s){
		}
		void showtime(){
			cout<<hour<<" hr "<<min<<" min "<<sec<<" sec"<<endl;
		}
		void operator=(CTime &a){
			this->hour=a.hour;
			this->min=a.min;
			this->sec=a.sec;
			}
};
int main(void){
	CTime t1(4,23,56.8);
	CTime t2;
	
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	cout<<"after process"<<endl;
	cout<<"T2=";
	t2=t1;
	t2.showtime();
}	