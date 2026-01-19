#include<iostream>
#include<string>
using namespace std;
class Shape{
	private:
		string color;
	public:
		Shape(string c = "white"):color(c){}

		virtual double area(void){
			return 0;
		}
				
		
		virtual void show(void){
			cout<<"Shape color :"<<color<<" area ="<<area()<<endl;
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

		virtual double area(){
			return (double)(width*height);
		}
		

		virtual void show(void){
			cout<<"Rectangle color :"<<show_color()<<", width :"<< width <<", height :"<<height<<" area ="<<area()<<endl;
		}
};

class Circle:public Shape{
	private:
		double radius;
	public:
		Circle(double r=1):radius(r),Shape("red"){}
		
		virtual double area(){
			return (double)(radius*radius*3.141592);
		}
		
	virtual void show(void){
			cout<<"Circle color :"<<show_color()<<", radius :"<<radius<<" area ="<<area()<<endl;
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