#include<iostream>
#include<string>
using namespace std;
struct student{
	int id;
	string name;
	float num;
};

void call(student);


int main(void){
	//input 3 student information
	student st[3];
	for(int i=0;i<3;i++){
		cin>>st[i].id;
		cin.get();
		getline(cin,st[i].name);
		cin>>st[i].num;
	}
	  for(int i = 0; i < 2; i++){
        for(int j = i + 1; j < 3; j++){
            if(st[i].id > st[j].id){
                student temp = st[i];
                st[i] = st[j];
                st[j] = temp;
            }
        }
    }
    // output all students
    cout << "\nSorted by ID:\n";
    for(int i = 0; i < 3; i++){
        call(st[i]);
    }
    for(int i = 0; i < 2; i++){
        for(int j = i + 1; j < 3; j++){
            if(st[i].num < st[j].num){
                student temp = st[i];
                st[i] = st[j];
                st[j] = temp;
            }
        }
    }
    // output all students
    cout << "\nSorted by num:\n";
    for(int i = 0; i < 3; i++){
        call(st[i]);
    }
    
    
	
return 0;
}

void call(student a){
	
	cout<<a.id<<"\t";
	cout<<a.name<<"\t";
	cout<<a.num<<endl;
	return;
}
