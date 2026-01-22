#include"cwin.h"
#include<iostream>

int main(void){
	
	const char* path="E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\Atlanta.txt";
	
	const char* output_upperpath="E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\upper.txt";
	const char* output_lowerpath="E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\lower.txt";
	//a
	size_t len =0;
	//b
	size_t space=0;
	//d
	size_t is=0;
	//e
		size_t a=0;
		size_t e=0;
		size_t ii=0;
		size_t o=0;
		size_t u=0;
	//a
	if(!count_words( path, len)){
		std::cout<<"in main open a ifile error"<<std::endl;
		return 1;
	}
	
	//b
	if(!count_space( path, space)){
		std::cout<<"in main open b ifile error"<<std::endl;
		return 1;
	}
	//d
	if(!count_is( path, is)){
		std::cout<<"in main open c ifile error"<<std::endl;
		return 1;
	}
	//e
	if(!count_aeiou( path, a,e,ii,o,u)){
		std::cout<<"in main open c ifile error"<<std::endl;
		return 1;
	}
	//f
	file_to_upper(path,  output_upperpath);
	std::cout<<"upper ok"<<std::endl;
	
	//g
	file_to_lower(path,  output_lowerpath);
	std::cout<<"lower ok"<<std::endl;
	//cout
	std::cout<<"all words = "<<len<<std::endl;
	std::cout<<"all words without space = "<<len-space<<std::endl;
	std::cout<<"how many words = "<<space<< std::endl;//betwin two words have one space;
	std::cout<<"how many is = "<<is<< std::endl;
	std::cout<<a<<" "<<e<<" "<<ii<<" "<<o<<" "<<u<< std::endl;
	
	
	
	return 0;
}
