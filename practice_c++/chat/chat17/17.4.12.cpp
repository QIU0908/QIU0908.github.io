#include<iostream>
#include<string>
using namespace std;
class Grand{
	protected:
		string name;
	public:
		Grand(string n):name(n){}
		
		void grandAction(){
			cout<<name<<" have a place !"<<endl;
		}
};

class Parent:public Grand{
	public:
		Parent(string n):Grand(n){}
		
	void parentAction(){
		cout<<name<<" have a house !"<<endl;
	}
};

class Child:public Parent{
	public:
		
		Child(string n):Parent(n){}
		
	void childAction(){
			cout<<name<<" have a car !"<<endl;
		}
};

int main(void){
	Child child("john");
	child.grandAction();
    child.parentAction();
    child.childAction();
}

