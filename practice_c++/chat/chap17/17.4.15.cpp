#include<iostream>
#include<string>
using namespace std;
class Grand{
	protected:
		string name;
	public:
		Grand(string n):name(n){}
		
		virtual ~Grand(){
        cout << "delete Grand" << endl;
    }
		
		void grandAction(){
			cout<<name<<" have a place !"<<endl;
		}
};

class Parent:public Grand{
	public:
		Parent(string n):Grand(n){}
		virtual ~Parent(){
        cout << "delete Parent" << endl;
    }
	void parentAction(){
		cout<<name<<" have a house !"<<endl;
	}
};

class Child:public Parent{
	public:
		
		Child(string n):Parent(n){}
		
		
	 virtual ~Child(){
        cout << "delete Child" << endl;
    }
	void childAction(){
			cout<<name<<" have a car !"<<endl;
		}
};

int main(void){
	Grand* g = new Child("john");
	g->grandAction();
    delete g;  
}

