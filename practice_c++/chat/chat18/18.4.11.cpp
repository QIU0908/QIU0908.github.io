#include<fstream>
#include<iostream>
#include<string>
using namespace std;

int main(void){
	
	string txt;
		ofstream ofile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\ccc.txt",ios::out);
		
		ifstream ifile1("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\aaa.txt",ios::in);
		ifstream ifile2("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\bbb.txt",ios::in);
		
if (!ofile) {
        cout << "Failed to open ccc.txt for writing" << endl;
        return 1;
    }
if (!ifile1) {
        cout << "Failed to open aaa.txt for writing" << endl;
        return 1;
    }
if (!ifile2) {
        cout << "Failed to open ccc.txt for writing" << endl;
        return 1;
    }

    while (getline(ifile1, txt)) {
        ofile << txt << endl;
    }


    while (getline(ifile2, txt)) {
        ofile << txt << endl;
    }
	
	if(ofile.is_open())
		cout<<"good"<<endl;
	else
		cout<<"not good"<<endl;
	ifile1.close();
	ifile2.close();	
	ofile.close();
	return 0;

	}