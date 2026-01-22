#include<iostream>
#include<fstream>
#include<string>

using namespace std;

	ifstream ifile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\Atlanta.txt", ios::in | ios::binary);
	ofstream ofile1("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\upper.txt", ios::out );
	ofstream ofile2("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\lower.txt", ios::out );

int main(void){
	
	ifile.seekg(0, ios::end);     
	size_t len = ifile.tellg();  
	ifile.seekg(0, ios::beg); 
	  
	string xxx(len,'\0');

	ifile.read((char*)&xxx[0],len);	
	
	size_t space_count = 0;
    size_t word_count = 0;
    bool in_word = false;

	int is=0,a=0,e=0,ii=0,o=0,u=0;
	
    for(size_t i = 0; i < len; i++) {
    	
    	char c = xxx[i];
    	
        if(c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            if(!in_word) {
				 word_count++; 
				 in_word = true; 
				 }
				 
        }else{
            	in_word = false;
            if(c == ' ') 
				space_count++;
        }
        
        if(xxx[i] == ' ' && xxx[i+1] == 'i'&& xxx[i+2] == 's'&& xxx[i+3] == ' '){
        		is++;
        		i++; 
        	}
        
        if(xxx[i] == 'a' || xxx[i] == 'A')	a++;
		if(xxx[i] == 'e'|| xxx[i] == 'E')	e++;
		if(xxx[i] == 'i'|| xxx[i] == 'I')	ii++;
		if(xxx[i] == 'o'|| xxx[i] == 'O')	o++;
		if(xxx[i] == 'u'|| xxx[i] == 'U')	u++;
		
		char upper_c = c;
        if (c >= 'a' && c <= 'z') upper_c = c - 'a' + 'A';
        ofile1.put(upper_c);
        
 		char lower_c = c;
        if (c >= 'A' && c <= 'Z') lower_c = c - 'A' + 'a';
        ofile2.put(lower_c);
    }
    ifile.close();
    ofile1.close();
    ofile2.close();
	
	cout<<"All = "<<len<< endl;
	cout<<"without space: "<<len-space_count<< endl;
	cout<<"how many words "<<space_count << endl;//betwin two words have one space;
	cout<<is<< endl;
	cout<<a<<" "<<e<<" "<<ii<<" "<<o<<" "<<u<< endl;
}