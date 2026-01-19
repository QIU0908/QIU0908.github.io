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
	
		
		Animal(const Animal &b){
			name=b.name;
			age=b.age;
			cout<<"Animal copy got call"<<endl;
		}
	};
		
class Dog:public Animal{	
	public:
		Dog(string n="puppy",int a=0):Animal(n,a){}
		
		Dog(const Dog &b):Animal(b){
			cout<<"Dog copy got call"<<endl;
			}
		};
class Cat:public Animal{	
	public:
		Cat(string n="pussy",int a=0):Animal(n,a){}
		
		Cat(const Cat &b):Animal(b){
			cout<<"Cat copy got call"<<endl;
			}
};


int main(void){
	Animal animal;
	
	Dog dog("Dog",3);
	
	Cat cat("Cat",5);
	
	animal.showInfo();
    dog.showInfo();
    cat.showInfo();
    
    Animal animalCopy(animal);
    Dog dogCopy(dog);
    Cat catCopy(cat);
    
    animalCopy.showInfo();
    dogCopy.showInfo();
    catCopy.showInfo();
    }        