#include<iostream>
using namespace std;
class CWin{
	private:
		char id ;
		int length;
		int width;
	public:
    CWin(char c, int l, int w){
        id = c;
        length = l;
        width = w;
    }	
		friend void showArea(CWin w){
			float area;
			area=w.length*w.width;
			cout<<w.id<<endl<<w.length<<endl<<w.width<<endl<<area;
		}
	};
	
int main(void){
	CWin win('A',10,20);
	
	showArea(win);
}