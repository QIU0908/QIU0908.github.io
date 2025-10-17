#include<iostream>
using namespace std;
int saleMoney(int a[5],int produce[5]);
void makeMoney(int a[5] ,int b[5] ,int c[5],int produce[5],int f[5]);
int main(void){
	int produce[5]={12,16,10,14,15};
	int 	  a[5]={33,32,56,45,33};
	int 	  b[5]={77,33,68,45,23};
	int 	  c[5]={43,55,43,67,65};
	int		  f[5];
	char   shit[5]={'a','b','c','d','e'};
	//a
	cout<<"A is sale number "<<saleMoney( a, produce)<<endl;
	cout<<"B is sale number "<<saleMoney( b, produce)<<endl;
	cout<<"C is sale number "<<saleMoney( c, produce)<<endl<<endl;
	//b
	makeMoney(a, b, c, produce, f);
	for(int i=0;i<5;i++){
		cout<<shit[i]<<" sales "<<f[i]<<" dollers"<<endl;
	}
	cout<<endl;
	//c
	if(saleMoney( a, produce)>saleMoney( b, produce)&&saleMoney( a, produce)>saleMoney( c, produce))
	cout<<"the best salesman is A";
	else if(saleMoney( b, produce)>saleMoney( a, produce)&&saleMoney( b, produce)>saleMoney( c, produce))
	cout<<"the best salesman is B";
	else
	cout<<"the best salesman is C";
	cout<<endl;
	//d
	makeMoney(a, b, c, produce, f);
	int num=f[0],y=0;
	for(int i=0;i<5;i++){
		if(f[i]>num){
			num=f[i];
			y=i;
		}		
	}
	cout<<shit[y]<<" is the best produce it make "<<num<<" dollers";
}
void makeMoney(int a[5] ,int b[5] ,int c[5],int produce[5],int f[5]){	
	for(int i=0;i<5;i++){
		f[i]=(a[i]+b[i]+c[i])*produce[i];
	}
}
int saleMoney(int a[5],int produce[5]){
	int num=0;
	int d[5];
	for(int i=0;i<5;i++){
		d[i]= produce[i]*a[i];
		num+=d[i];
	}
	return num;
}