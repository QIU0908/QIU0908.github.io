#include<iostream>
using namespace std;

class CRectang{
	private:
		int width;
		int height;
	public:
		CRectang(int w,int h){
			width=w;
			height=h;
		}
		
		CRectang(){
			width=10;
			height=10;
		}
};