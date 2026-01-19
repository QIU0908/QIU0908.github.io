#include<iostream>
using namespace std;

void check_prime(int n){
	try{
		if(n<0)
			throw "out of boundary";
			
		if(n<2){
            cout << n << " is not a prime number" << endl;
            return;
        }

        for(int i=2; i<n; i++){
            if(n % i == 0){
                cout << n << " is not a prime number" << endl;
                return;
            }
        }

        cout << n << " is a prime number" << endl;
    }
	
	catch(const char *str){
		cout<<n<<", "<<str<<endl;
	}
}

int main(void){
	for(int i=-2;i<=10;i++){
		check_prime(i);
	}
}
