#include<iostream>
#include<string>
using namespace std;

class CT{
	public:
	int width;
	int height;
	string title;
	
	void set_title(string b){
	 title=b;
	}
};

void display(CT a){
	cout<<a.title;
}

int main(void){
	CT w;
	string f;
	getline(cin,f);
	w.set_title(f);
	display(w);
}