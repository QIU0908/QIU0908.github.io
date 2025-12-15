#include<iostream>
#include<string>
using namespace std;
class Animal{
	public:
		virtual void makesound()=0;
};
class FlyingCreature{
	public:
		virtual void fly()=0;
};

class Sparrow:public Animal,FlyingCreature{
	public:
	virtual void makesound()override{
		cout<<"Sparrow ge ge ge";
	}
	virtual void fly()override{
		cout<<"fly height"<<endl;
	}
};

class Chicken:public Animal,FlyingCreature{
	public:
	virtual void makesound()override{
		cout<<"Chicken ge ge ge";
	}
	virtual void fly()override{
		cout<<"fly low"<<endl;
	}
};

int main(void){
	Sparrow sparrow;
	Chicken chicken;
	sparrow.makesound();
	sparrow.fly();
    chicken.makesound();
    chicken.fly();
}