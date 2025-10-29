#include<iostream>

using namespace std;

void release(int **);

int main(void){
int *a,*b;
a = new int[3];
b = new int[3];
 	a[0] = 100; a[1] = 200; a[2] = 300;
    b[0] = 400; b[1] = 500; b[2] = 600;
    
    cout<<*a<<endl;
    
for(int i=0;i<3;i++){
	a[i]+=b[i];
	cout<<a[i]<<"\t";
}cout<<endl;
release(&a);
release(&b);
cout<<*a<<endl;
 if (a == nullptr)
        cout <<"wgg ";
}

void release(int **a){
	delete[] *a;
	*a=nullptr;
}