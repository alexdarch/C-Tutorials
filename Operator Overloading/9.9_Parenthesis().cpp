// 9.9_Parenthesis().cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>

//Overload operator() to return the substring that starts at the index of the first parameter.The length of the substring should be defined by the second parameter.

//Hint : You can use array indices to access individual chars within the std::string
//Hint : You can use operator+= to append something to a string
class Mystring
{
private:
	std::string m_str;

public:
	Mystring(std::string str)
		:m_str{ str }
	{
	}

	std::string operator()(int start, int length)
	{
		assert(start + length <= m_string.length() && "Mystring::operator(int, int): Substring is out of range");

		std::string subStr = "";
		for (int index = start; index < start + length; index++)
		{
			subStr += m_str[index];
		}
		return subStr;
	}

};

int main()
{
	Mystring string("Hello, world!");
	std::cout << string(7, 5); // start at index 7 and return 5 characters

    return 0;
}

