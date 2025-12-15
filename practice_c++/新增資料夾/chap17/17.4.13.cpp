#include<iostream>
#include<string>
using namespace std;
class Animal{
	public:
		virtual void makesound()=0;
		virtual ~Animal(){
		cout<<"delete ANImal"<<endl;
		}
};
class FlyingCreature{
	public:
		virtual void fly()=0;
		
		virtual ~FlyingCreature(){
		cout<<"delete FlyingCreature"<<endl;
		}
		
};

class Sparrow:public Animal,public FlyingCreature{
	public:
	virtual void makesound()override{
		cout<<"Sparrow ge ge ge";
	}

	virtual void fly()override{
		cout<<"fly height"<<endl;
	}
	
	virtual ~Sparrow(){
		cout<<"delete Sparrow"<<endl;
		}
};

class Chicken:public Animal,public FlyingCreature{
	public:
	virtual void makesound()override{
		cout<<"Chicken ge ge ge";
	}
	virtual void fly()override{
		cout<<"fly low"<<endl;
	}
	
		virtual ~Chicken(){
		cout<<"delete Chicken"<<endl;
		}
};

int main(void){
	 Animal* a = new Sparrow;
    FlyingCreature* f = new Sparrow;

    a->makesound();
    f->fly();

    delete a;
    delete f;
}