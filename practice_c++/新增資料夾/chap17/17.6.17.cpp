#include<iostream>
using namespace std;
template<class T,int n>
class CArray{
	protected:
		T arr[n];
	public:
		CArray(){
			for(int i=0;i<n;i++)
				arr[i]=0;
		}
		void set_data(){
			for(int i=0;i<n;i++){
				cout<<"input value for arr"<<"["<<i<<"]";
				cin>>arr[i];
			}
				
		}
		void show_data(){
			cout<<"show data called ..."<<endl;
			for(int i=0;i<n;i++)
				cout<<"arr"<<"["<<i<<"]"<<arr[i]<<endl;
		}
};

int main(void){
	CArray<int,5> my_array;
	my_array.set_data();
	my_array.show_data();
}