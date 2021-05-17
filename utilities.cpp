#include "utilities.h"

int digitsOfNumber(int x) {
    x = abs(x);
	int n = 1;
	while ((x /= 10) > 0)
		n++;
	return n;
}

int GCD(int a, int b) {
    if (a == 0 || b == 0) return 1;
    long div;
    if (a == b)  return a;
    long d = a - b;
    if (d < 0) {
        d = -d;  div = GCD(a, d);
    }
    else
        div = GCD(b, d);
    return div;
}

int LCM(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return a * b / GCD(a, b);
}

#ifdef __linux__
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
void clear() {
    std::system("cls");
}
#endif