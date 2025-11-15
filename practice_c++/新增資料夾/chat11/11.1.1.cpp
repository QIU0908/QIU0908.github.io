#include<iostream> 
#include<string> 
using namespace std; 
struct student{ 
	int id; 
	string name; 
	int midNum; 
	int endNum; 
	int allNum; 
}student; 


int main(void){ 
	cin>>student.id; 
	cin.get();
	getline(cin, student.name);
 	cin>>student.midNum;
  	cin>>student.endNum;
   	cin>>student.allNum;
   
float avg=(student.midNum)*0.3+(student.endNum)*0.3+(student.allNum)*0.4;
  	cout<<student.id<<endl;
   	cout<<student.name<<endl;
    cout<<"midNum"<<student.midNum<<endl;
	cout<<"endNum"<<student.endNum<<endl;
	cout<<"allNum"<<student.allNum<<endl;
	cout<<"avgNum"<<avg;
    } 
	