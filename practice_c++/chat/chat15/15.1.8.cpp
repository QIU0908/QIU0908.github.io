#include<iostream>
using namespace std;
class Cwin{
	private:
		char id;
		int width,height;
	public:
		Cwin(char i,int w,int h):id(i),width(w),height(h){
		}
		
		int area(void){
			return width*height;
		}
};

bool operator<( Cwin &a,  Cwin &b){
			return (a.area() < b.area());
		}
		
bool operator<( Cwin &a,const  int &var){
			return (a.area() < var);
		}


int main(void){
	Cwin win1('A',70,80);
	Cwin win2('B',60,90);
	
	if(win1<win2){
		cout<<"Win1<win2"<<endl;
	}else{
		cout<<"Win2<win1"<<endl;
	}
	
	if(win1<7000){
		cout<<"Win1<7000"<<endl;
	}else{
		cout<<"7000<win1"<<endl;
	}
	
	if(win2<4500){
		cout<<"Win2<4500"<<endl;
	}else{
		cout<<"4500<win2"<<endl;
	}
	
	return 0;
	
}