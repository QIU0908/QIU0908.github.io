#include <iostream>
#include <fstream>
#include <cstdlib>   // rand, srand

using namespace std;

int main() {
	ofstream ofile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\rand.txt",ios::out);
    srand(3); 

    for (int i = 0; i < 1000; i++) {
        int r = rand() % 9999 + 1; 
         ofile << r << endl;
    }

	ofile.close();
    cout << "1000 random numbers written to rand.txt" << endl;
    ifstream ifile("E:\\portable_wcm2025\\data\\tmp\\qiu\\practice_c++\\chat\\chat18\\rand.txt",ios::in);
    long long sum = 0;  
    int num;

    while (ifile >> num) {
        sum += num; 
    }
    ifile.close();
    double average = double(sum) / 1000;
    cout << "Average: " << average << endl;
    return 0;
}