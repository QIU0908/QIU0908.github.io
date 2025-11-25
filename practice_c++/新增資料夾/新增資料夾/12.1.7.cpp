#include<iostream>
using namespace std;
class CBox {
	public:
	float lenth;
	float width;
	float height;
	
	float volume(void){
		return lenth*width*height;
	}
	
	float surface(void){
		return 2*(lenth*width)+2*(width*height)+2*(lenth*height);
	}
};

int main(void){
	CBox w;
	cin>>w.lenth>>w.width>>w.height;
	cout<<w.volume()<<endl;
	cout<<w.surface();
}