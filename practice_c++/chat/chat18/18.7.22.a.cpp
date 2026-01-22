#include"cwin.h"

	bool count_words(const char* path,size_t & len){
		
		std::ifstream ifile(path,std::ios::binary);
		
		if(!ifile){
			std::cout<<"in a.hpp open file error"<<std::endl;
			return false;
		}else{
			len=0;
			char ch;
			while(ifile.get(ch))
			 len++;
		}
		return true;
	}