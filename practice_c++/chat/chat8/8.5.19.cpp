#include<iostream>
#include<string>
using namespace std;

int t(string ,char ,char );

int main(void){
	string r;
	int d;
	cout<<"pleace input string : ";
	getline(cin, r);
	cout<<"string are "<<r<<endl;
	cout<<"in this you use eash (a e i o u) times"<<endl;

	
	cout<<"A,a= "<<t(r,'A','a')<<endl;
	cout<<"E,e= "<<t(r,'E','e')<<endl;
	cout<<"I,i= "<<t(r,'I','i')<<endl;
	cout<<"O,o= "<<t(r,'O','o')<<endl;
	cout<<"U,u= "<<t(r,'U','u')<<endl;
	
	int b=r.length();
	  for(int i = 0; i < b; i++){
        if(r[i]!='A'&&r[i]!='a'&&
           r[i]!='E'&&r[i]!='e'&&
           r[i]!='I'&&r[i]!='i'&&
           r[i]!='O'&&r[i]!='o'&&
           r[i]!='U'&&r[i]!='u'){
            d++;
        }
    }

	cout<<"other="<<d;
}

int t(string r,char A,char a){
	int b=r.length();
	int d=0;
	for(int i=0;i<b;i++){
		if(r[i]==A||r[i]==a){
			d+=1;
		}	
	}
	return d;
}