#include"cwin.h"

bool count_is(const char* path,size_t& is){
		
		std::ifstream ifile(path,std::ios::binary);
		
		if(!ifile){
			std::cout<<"in a.hpp open file error"<<std::endl;
			return false;
		}else{
			//to know len how long
			ifile.seekg(0, std::ios::end);
    		size_t len = ifile.tellg();
    		ifile.seekg(0, std::ios::beg);
    		
    		//creata a enty string "content"
			std::string content(len, '\0'); 
			//put ifile in to "content" start with 0
			ifile.read(&content[0], len);
			
			//this i using size_t because int mybe not big anought
			//i + 3<len because i need to jump off last if loop"i+3"
			for(size_t i=0;i + 3<len;i++){
				if (content[i] == ' ' &&
            	content[i + 1] == 'i' &&
            	content[i + 2] == 's' &&
            	content[i + 3] == ' ') {
            	is++;
				}	
			}
		}
		return true;
	}