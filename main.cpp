#include <iostream>
#include <iomanip>

#include "fraction.h"

using namespace std;

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void clear() {
    std::system("clear");
}

char _getch(void) {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    //old.c_cc[VGoodIME] = 0;
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    printf("%c\n", buf);
    return buf;
}
#elif _WIN32
#include <conio.h>
void clear() {
    std::system("cls");
}
#endif

int digitsOfNumber(int x){
    int n = 1;
	while ((x /= 10) > 0) 
        n++;
	return n;
}

class Matrix{
private:
    int rows;
    int columns;
    int *ptr;
    bool filled;
public:
    void fillArray(int size){
        if(filled){
            delete[] ptr;
            filled = false;
        }
        cout << "How much rows? ";
        cin >> rows;
        cout << "How much columns? ";
        cin >> columns;
        ptr = new int[rows*columns];
        for(int i = 0; i < rows * columns; i++){
            ptr[i] = 0;
        }
        int curPos = 0;

    }
    void showArray(int curPos = -1){
       // for(int i = 0;)
    }
};

int main(){
    Fraction a(13, 6);
    a /= Fraction(7, 0);
    cout << a << endl;
    //cout << 321%10 << endl;
}