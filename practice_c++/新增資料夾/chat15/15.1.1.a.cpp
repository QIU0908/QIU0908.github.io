#include<iostream>
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
};
int main(void){
	CTime t1(4,23,56.8);
	CTime t2(5,45,30.3);
	
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	return 0;
}