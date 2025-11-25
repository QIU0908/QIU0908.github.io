#include<iostream>
using namespace std;
class win{
  public:
	char id;
	int width;
	int height;

int area(void){
	return width * height;
	}

};

int main(void){
	class win win1;
	 
	 win1.id='A';
	 win1.width=50;
	 win1.height=40;
	 
	 cout<<win1.area();
}