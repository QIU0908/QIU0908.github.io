#include<iostream>

namespace name1{
	int var=5;
}

namespace name2{
	int var=15;
}

int main(void){
	using std::cout;
	using std::endl;
	cout<<name1::var<<endl;
	cout<<name2::var<<endl;
	return 0;
}
