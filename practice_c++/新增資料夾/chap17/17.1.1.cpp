#include<iostream>
#include<string>
using namespace std;
class Shape{
	private:
		string color;
	public:
		Shape(string c = "white"):color(c){}
		
		virtual void show(void){
			cout<<"Shape color :"<<color<<endl;
		}
		
		
		string show_color(){
			return color;
		}
};

class Rectangle:public Shape{
	private:
		int width,height;
	public:
		Rectangle(int w=1,int h=1):width(w),height(h),Shape("yellow"){}

		virtual void show(void){
			cout<<"Rectangle color :"<<show_color()<<", width :"<< width <<", height :"<<height<<endl;
		}
};

class Circle:public Shape{
	private:
		double radius;
	public:
		Circle(double r=1):radius(r),Shape("red"){}
	virtual void show(void){
			cout<<"Circle color :"<<show_color()<<", radius :"<<radius<<endl;
		}
};

int main(void){
	Shape shape;
	Rectangle rectangle(5,3);
	Circle circle(2.5);
	
	shape.show();
	rectangle.show();
	circle.show();
}