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
		CTime operator-(const CTime &t){
			int h=0, m=0;
			double s=0;
			s=this->sec - t.sec;
			if(s<0){
				s=60+s;
				m--;
			}
			m+=this->min - t.min;
			if(m<0){
				m=60+m;
				h--;
			}
			h+=this->hour - t.hour;
			return CTime(h,m,s);
		}
			
};
int main(void){
	CTime t1(6,23,16.3);
	CTime t2(3,45,35.8);
	
	CTime t3=t1-t2;
	t3.showtime();
	
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	return 0;
}