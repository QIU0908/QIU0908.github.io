#include<iostream>
#include<string>
using namespace std;

enum month{
	jun=1,
	feb,
	mar,
	apr,
	may,
	jen,
	jui,
	aug,
	set,
	octm,
	nov,
	decm,
};

string monthToString(month);

int main() {
	month a;
    int temp;
    cin >> temp;         
    a = static_cast<month>(temp);
    cout << monthToString(a) << endl;
}

string monthToString(month m) {
    switch (m) {
        case jun: return "jun";
        case feb: return "feb";
        case mar: return "mar";
        case apr: return "apr";
        case may: return "may";
        case jen: return "jen";
        case jui: return "jui";
        case aug: return "aug";
        case set: return "set";
        case octm: return "oct";
        case nov: return "nov";
        case decm: return "dec";
        default: return "unknown";
    }
}