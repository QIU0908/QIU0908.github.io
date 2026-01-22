#ifndef CWIN_H
#define	CWIN_H
	#include<fstream>
	#include<iostream>
	#include<string>
	bool count_words(const char* path,size_t& len);
	bool count_space(const char* path,size_t& space);
	bool count_is(const char* path,size_t& is);
	bool count_aeiou(const char* path,size_t& a,size_t&e,size_t&ii,size_t&o,size_t&u);
	void file_to_upper(const char* input_path, const char* output_path);
	void file_to_lower(const char* input_path, const char* output_path);
#endif
