#include "Custom Functions.h"
/****************************************************************************/
/*!
\file Custom Functions.cpp
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A bunch of custom made functions to handle numbers and letters in various situations
*/
/****************************************************************************/

/****************************************************************************/
/*!
\brief
Function to check if a number is odd
\param num
		the value that will be checked against
*/
/****************************************************************************/
int isOdd(const int num)
{
	return num & 1;
}
/****************************************************************************/
/*!
\brief
Function to check if a number is negative
\param num
		the value that will be checked against
*/
/****************************************************************************/
bool isNegative(const double num)
{
	if(num > 0)
	{
		return false;
	}
	return true;
}
/****************************************************************************/
/*!
\brief
Function to check if a character is a character of a number
\param c
		the char that will be checked against
*/
/****************************************************************************/
bool isNumber(char c)
{
	if(c >= '0' && c <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
/****************************************************************************/
/*!
\brief
Function to check if a character is a a character of an alphabet
\param c
		the char that will be checked against
*/
/****************************************************************************/
bool isLetter(char c)
{
	if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
/****************************************************************************/
/*!
\brief
Function that can check if two characters are the same regardless of capitalization
\param c
		first value in the comparison
\param letter
		second value in the comparison
*/
/****************************************************************************/
bool isSameLetter(char c, char letter)
{
	if(letter >= 'a' && letter <= 'z')
	{
		if(c == letter || c == (letter - 32))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(c == letter || c == (letter + 32))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
/****************************************************************************/
/*!
\brief
Function to check if a character is capital
\param c
		the char that will be checked against
*/
/****************************************************************************/
bool isCapital(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
/****************************************************************************/
/*!
\brief
Function that converts a character into an appropriate number
\param c
		the char that will be converted
*/
/****************************************************************************/
int convertToNumber(char c)
{
	if(isLetter(c))
	{
		if(isCapital(c))
		{
			return c - 64;
		}
		else
		{
			return c - 96;
		}
	}
	else if(c == '-')
	{
		return -1;
	}
	else
	{
		return c - 48;
	}
}
/****************************************************************************/
/*!
\brief
Function that capitalizes a character if it isn't
\param c
		the character that will be capitalized
*/
/****************************************************************************/
char capitalize(char c)
{
	if(isCapital(c))
	{
		return c;
	}
	else
	{
		return c - 32;
	}
}
/****************************************************************************/
/*!
\brief
Function that converts a string of chars to a number
\param string
		the string of chars that will be converted into a number
*/
/****************************************************************************/
int convertToNumber(char* string)
{
	vector<int> numbers;
	int number = 0;
	int NumOfDigits;
	
	for(NumOfDigits = 0; string[NumOfDigits]; NumOfDigits++)
	{
		numbers.push_back(convertToNumber(string[NumOfDigits]));
	}
	if(numbers[0] == -1)
	{
		for(int index = 1; index < NumOfDigits; index++)
		{
			number -= numbers[index] * pow((double)10,NumOfDigits - index - 1);
		}
	}
	else
	{
		for(int index = 0; index < NumOfDigits; index++)
		{
			number += numbers[index] * pow((double)10,NumOfDigits - index - 1);
		}
	}
	return number;
}