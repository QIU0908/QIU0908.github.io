#include <iostream>
#include <fstream>
#include <cstdlib>   // rand, srand

using namespace std;

int main() {
	ofstream ofile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\rand.dat",ios::binary);
    srand(3); 
    for (int i = 0; i < 1000; i++) {
        int r = rand() % 9999 + 1; 
         ofile.write((char*)&r,sizeof(r));
    }
	ofile.close();
	
	
	ifstream ifile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\rand.dat",ios::binary);
	int a=0,b,c=0;
	

		while(ifile.read((char*)&b,sizeof(b))){
			if(b>a){
				a=b;
			}
			c+=b;
		}
		ifile.close();
		
		cout<<a<<endl;
		cout<<(double)c/1000<<endl;
		
}