#ifndef _CUSTOM_FUNCTIONS_H
#define _CUSTOM_FUNCTIONS_H
/****************************************************************************/
/*!
\file Custom Functions.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A bunch of custom made functions to handle numbers and letters in various situations
*/
/****************************************************************************/
#include <iostream>
#include <limits.h>
#include <vector>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int isOdd(const int);
bool isNegative(const double);
bool isNumber(char);
bool isLetter(char);
bool isCapital(char);
bool isSameLetter(char, char);
int convertToNumber(char);
int convertToNumber(char* string);
char capitalize(char c);

#endif