#include <iostream>
using namespace std;

class CWin{
protected:
    char id;
    int width, height;

public:
    CWin(char i='D', int w=10, int h=10){
        id = i;
        width = w;
        height = h;
    }

    void show_area(void){
        cout << "Window " << id << ", area = "
             << area() << endl;
    }

    virtual int area(void){
        return width * height;
    }
};

class CMiniWin : public CWin{
public:
    CMiniWin(char i, int w, int h) : CWin(i, w, h) {} 

    virtual int area(void){
        return (int)(0.8 * width * height);
    }
};

void display(CWin &win){
	win.show_area();
}

int main(void){
	CWin win('a',70,80);
	CMiniWin m_min('b',50,60);
	
	display(win);
	display(m_min);
}