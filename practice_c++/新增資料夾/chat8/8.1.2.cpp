#include<iostream>
using namespace std;

int main(void){
	int data1[5]={26,5,7,63,81};
	int data2[5]={1,9,52,64,40};
	int data3[10];
	
	
	
for(int i=0;i<=4;i++){
	data3[i]=data1[i];
}
for(int i=0;i<=4;i++){
	data3[i+5]=data2[i];
}

for(int i=0;i<10;i++){
	for(int j=i+1;j<10;j++){
		
		if(data3[j]>data3[i]){
			int temp = data3[i];//use temp save data3[i]
			data3[i]=data3[j];// data3[j]'s number put it in data3[i],so data3[j]'s number is gone.
			data3[j]=temp;//use data3[i]'s number(=temp) put it in data3[j],so we can change the number.
		}
		
	}
		
}

for(int i=0;i<10;i++){
	cout<<data3[i];
		
}



}
