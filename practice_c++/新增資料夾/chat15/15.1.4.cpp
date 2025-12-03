#include<iostream>
#include <cmath>
using namespace std;
class CTime{
	private:
		int hour,min;
		double sec;
	public:
		CTime(int h,int m,double s):hour(h),min(m),sec(s){
		}
		void showtime(){
			cout<<hour<<" hr "<<min<<" min "<<sec<<" sec"<<endl;
		}
		CTime operator/(const int var){
			int h=0, m=0;
			double s=0,total=0;
			total=this->hour*3600+this->min*60+this->sec;
			total/=var;
			h=total/3600;
			 total = fmod(total, 3600);
			m=total/60;
			s = fmod(total, 60); 
			return CTime(h,m,s);
		}	
};
int main(void){
	CTime t1(6,35,41.5);
	CTime t2=t1/3;
	
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	return 0;
}