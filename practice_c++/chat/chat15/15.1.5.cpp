#include<iostream>
using namespace std;
class Cwin{
	private:
		char id;
		int width,height;
	public:
		Cwin(char i,int w,int h):id(i),width(w),height(h){
		}
		
		int area(void)const{
			return  width*height;
		}
};

bool operator<(const Cwin &a, const Cwin &b){
			return a.area() < b.area();
		}
		


int main(void){
	Cwin win1('A',70,80);
	Cwin win2('B',60,90);
	
	if(win1<win2){
		cout<<"Win1<win2"<<endl;
	}else{
		cout<<"Win2<win1"<<endl;
	}
}	
	
	