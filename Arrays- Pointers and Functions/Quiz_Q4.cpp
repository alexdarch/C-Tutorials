// Quiz_Q4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

void printCString(const char *str) //could have used str[], but it decays to a pointer anyways so might as well make that explicit
{
	while (*str != '\0') //c-style strings are weird, they are auto de-referenced when the program knows how long it is but you need to dereference explicitly
		//when passed to a function due to the decay
	{
		std::cout << *str++;		//str++ because we want to print and then increment
	}


}


int main()
{
	char cString[] = "Hello World";

	std::cout << cString; //notice that here, the compliler has auto de-referenced cString (since it is a pointer) and printed the whole thing

	std::cout << "\n";

	printCString(cString); //here the cString decays to a pointer like normal so need to dereference in the functoin

	
    return 0;
}

