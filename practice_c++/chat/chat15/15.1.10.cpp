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
		double total(){
			double total=hour*3600+min*60+sec;
			return total;
		}
};

bool operator>(CTime &t1,CTime &t2){
	return (t1.total()>t2.total());
}

bool operator<(CTime &t1,CTime &t2){
	return (t1.total()<t2.total());
}


int main(void){
	CTime t1(4,23,56.8);
	CTime t2(5,45,30.3);
	cout<<"T1=";
	t1.showtime();
	cout<<"T2=";
	t2.showtime();
	
	if(t1>t2)
	cout<<"t1 bigger than t2"<<endl;
	else
	cout<<"t2 bigger than t1"<<endl;
	
	if(t1<t2)
	cout<<"t1 smaller than t2"<<endl;
	else
	cout<<"t2 smaller than t1"<<endl;
	
	return 0;
}