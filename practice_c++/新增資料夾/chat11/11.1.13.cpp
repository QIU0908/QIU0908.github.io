#include<iostream>

using namespace std;

 typedef struct my_time {
    int hour;
    int minute;
    float second;
};

 int main() {

    my_time t[3] = {
        {6, 24, 17.43}, 
        {3, 40, 45.58},  
        {0, 0, 0}       
    };

    float sec_diff = t[0].second - t[1].second;
    int borrow_min = 0;
    if (sec_diff < 0) {
        sec_diff += 60;
        borrow_min = 1;
    }

    int min_diff = t[0].minute - t[1].minute - borrow_min;
    int borrow_hour = 0;
    if (min_diff < 0) {
        min_diff += 60;
        borrow_hour = 1;
    }

    int hour_diff = t[0].hour - t[1].hour - borrow_hour;

    t[2].hour = hour_diff;
    t[2].minute = min_diff;
    t[2].second = sec_diff;

    
    for(int i = 0; i < 3; i++) {
        cout << "t[" << i << "] = "
             << t[i].hour << ":"
             << t[i].minute << ":"
             << t[i].second << endl;
    }

    return 0;
}
    
    