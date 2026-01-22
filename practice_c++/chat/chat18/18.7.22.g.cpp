#include"cwin.h"

	void file_to_lower(const char* input_path, const char* output_path){
		std::ifstream ifile(input_path, std::ios::binary);
    	std::ofstream ofile(output_path, std::ios::out);
    	
    	char c;
    	 
    	while (ifile.get(c)) {
        char lower_c = (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
        ofile.put(lower_c);
    	}
	}