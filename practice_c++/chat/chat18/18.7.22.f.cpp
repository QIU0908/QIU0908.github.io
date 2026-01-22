#include"cwin.h"

	void file_to_upper(const char* input_path, const char* output_path){
		std::ifstream ifile(input_path, std::ios::binary);
    	std::ofstream ofile(output_path, std::ios::out);
    	
    	char c;
    	 
    	while (ifile.get(c)) {
        char upper_c = (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
        ofile.put(upper_c);
    	}
	}