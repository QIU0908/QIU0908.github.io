#include"cwin.h"

bool count_aeiou(const char* path,size_t& a,size_t&e,size_t&ii,size_t&o,size_t&u){
		
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
			
			for(size_t i=0;i <len;i++){
				        if(content[i] == 'a'|| content[i] == 'A')	a++;
						if(content[i] == 'e'|| content[i] == 'E')	e++;
						if(content[i] == 'i'|| content[i] == 'I')	ii++;
						if(content[i] == 'o'|| content[i] == 'O')	o++;
						if(content[i] == 'u'|| content[i] == 'U')	u++;
			}	
		}
		
		return true;
	}