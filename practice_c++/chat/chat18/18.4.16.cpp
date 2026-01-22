#include<fstream>
#include<iostream>
#include<string>
using namespace std;

int main(void){
	
		char txt[800];
		string xcc;
	
		ofstream ofile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\ccc.dat",ios::trunc|ios::binary );
		
		ifstream ifile1("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\aaa.txt",ios::in);
		ifstream ifile2("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\bbb.txt",ios::in);
		
		
    while(ifile1.getline(txt,800)){
        xcc+=txt;
        xcc+='\n';
    }

    while(ifile2.getline(txt,800)){
        xcc+=txt;
        xcc+='\n';
    }

	ifile1.close();
	ifile2.close();	
	
	size_t len = xcc.size();  
	
	ofile.write((char*)&len, sizeof(len));
	ofile.write(xcc.data(), len);       
	ofile.close();
	
	ifstream ifile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\ccc.dat",ios::binary );
	ifile.read((char*)&len, sizeof(len));

	string readback(len, '\0');  
	
	ifile.read(&readback[0], len);

	cout << readback << endl;

return 0;
}