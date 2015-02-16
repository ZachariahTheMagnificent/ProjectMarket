#include "Custom Functions.h"

int isOdd(const int num)
{
	return num & 1;
}

bool isNegative(const double num)
{
	if(num > 0)
	{
		return false;
	}
	return true;
}

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