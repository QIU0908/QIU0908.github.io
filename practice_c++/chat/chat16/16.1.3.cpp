#include<iostream>
#include<string>
using namespace std;

class Animal{
	private:
		string name;
		int age;
	public:
		Animal(string n="animal",int a=1):name(n),age(a){}
		
		void showInfo(){
			cout<<name<<"\t"<<age<<endl;
		}
		};
		
class Dog:public Animal{	
	public:
		Dog(string n="puppy",int a=0):Animal(n,a){}
		};
class Cat:public Animal{	
	public:
		Cat(string n="pussy",int a=0):Animal(n,a){}
		
};


int main(void){
	Animal animal;
	Dog dog("Dog",3);
	Cat cat("Cat",5);
	animal.showInfo();
    dog.showInfo();
    cat.showInfo();
    };          