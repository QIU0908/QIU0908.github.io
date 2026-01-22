#include"cwin.h"

	bool count_space(const char* path,size_t& space){
		
		std::ifstream ifile(path,std::ios::binary);
		
		if(!ifile){
			std::cout<<"in b.hpp open file error"<<std::endl;
			return false;
		}else{
			space=0;
			char ch;
			while(ifile.get(ch)){
				if(ch==' '){
					space++;
				}
			}
				
			
			 
		}
		return true;
	}