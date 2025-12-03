#include<iostream>
using namespace std;
class CTime{
	private:
		int hour,min;
		double sec;
	public:
		CTime(int h=1,int m=1,double s=1):hour(h),min(m),sec(s){
		}
		void showtime(){
			cout<<hour<<" hr "<<min<<" min "<<sec<<" sec"<<endl;
		}
		void set_time(int h=1,int m=1,double s=1){
			hour=h;
			min=m;
			sec=s;
		}
		
		CTime operator+(const CTime &t){
			int h=0,m=0;
			double s=0;
			s=this->sec+t.sec;
			if(s>=60.){
				s=s-60.;
				m++;
			}
			m+=this->min+t.min;
			if(m>=60.){
				m=m-60.;
				h++;
			}
			h+=this->hour+t.hour;
			return CTime(h,m,s);
		}
		
		
		
};
int main(void){
	CTime t1(4,23,56.8);
	CTime t2(5,45,30.3);
	CTime t3=t1+t2;
	t3.showtime();
	
	
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	return 0;
}