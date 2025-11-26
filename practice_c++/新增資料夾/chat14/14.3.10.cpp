#include<iostream>
using namespace std;

class Caaa{
	private:
		int total,* ptr;
	public:
		Caaa(int num):total(num){
			ptr=new int [total];
			for(int i=0;i<total;i++){
				cout<<"input arr["<<i<<"] : ";
				cin>>ptr[i];
			}
		}
		
		void show(void){
			for(int i=0;i<total;i++){
			cout<<"arr ["<<i<<"] = "<<ptr[i]<<endl;
			}
		}
		
		Caaa(const Caaa& a){
			cout<<"call COPY"<<endl;
			total=a.total;
			ptr=new int [total];
			for(int i=0;i<total;i++){
				ptr[i]=a.ptr[i];
			}
		}
		
		~Caaa(){
			cout<<"call DELETE"<<endl;
			
			delete [] ptr ;
			system("pause");
		}
		
};
int main(void){
	Caaa a(3);
	Caaa b(a);
	cout<<"--aa--"<<endl;
	a.show();
	cout<<"--bb--"<<endl;
	b.show();
}