#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

int digitsOfNumber(int x);

int GCD(int a, int b); //greatest common division

int LCM(int a, int b); //least common multiple

void clear();

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

char _getch(void);

#elif _WIN32
#include <conio.h>
#endif

#endif