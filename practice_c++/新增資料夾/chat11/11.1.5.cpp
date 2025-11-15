#include<iostream>
#include<string>
using namespace std;
struct student{
	int id;
	string name;
	int midNum;
	int endNum;
	int allNum;
};

void call(student);

int main(void){
	//input 3 student information
	student st[3];
	for(int i=0;i<3;i++){
		cin>>st[i].id;
		cin.get();
		getline(cin,st[i].name);
		cin>>st[i].midNum;
		cin>>st[i].endNum;
		cin>>st[i].allNum;	
	}
	//find which person information
	cout<<"find which person ? id ";
	int id;
	bool found=0;
	
	cin>>id;
	for(int i=0;i<3;i++){
		if(id==st[i].id){
			call(st[i]);
			found=1;
		}
	}
	if(found==0){
		cout<<"not found";
	}
return 0;
}

void call(student a){
	float avg=(a.midNum)*0.3+(a.endNum)*0.3+(a.allNum)*0.4;
	cout<<a.id<<endl;
	cout<<a.name<<endl;
	cout<<"midNum"<<a.midNum<<endl;
	cout<<"endNum"<<a.endNum<<endl;
	cout<<"allNum"<<a.allNum<<endl;
	cout<<"avgNum"<<avg;
	return;
}