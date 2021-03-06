// 7.11_Recursion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int factorial(int multiplier)
{
	std::cout << multiplier;

	if (multiplier <= 1)	//termination condition (could be <= 1 or 0). Left as 1 to make cout prettier
		return 1;

	std::cout << " * ";

	return factorial(multiplier - 1)*multiplier;

}

int sumOfDigits(int num)
{
	std::cout << num  % 10;		//shows that this adds the numbers from last to first

	if (num <= 9)			//termination condition
	{
		std::cout << "\n";
		return num;
	}
	else 
	{
		std::cout << " + ";
		return num % 10 + sumOfDigits((num - (num % 10)) / 10);		//subtract the last digit so it is a multiple of 10, then divide by 10 and call sumOfDigits
	}
}

void printBinary(unsigned int num)		//unsigned forces -ve numbers to overflow to +ve ones so that we can convert to binary (overflow is done via twos complement)
{
	if (num < 1)
		return;		//termination condition
	else
	{
		printBinary((num - (num % 2)) / 2);
		std::cout << num % 2;
	}
}


int main()
{
	int fact = 7;
	std::cout << "\n" << fact << "! = " << factorial(fact) << "\n";

	int digits = 93427;
	std::cout << "The sum of the digits of " << digits << " is " << sumOfDigits(digits) << "\n";

	int bin = -15;
	std::cout << "\nThe binary representation of " << bin << " is ";
	printBinary(bin);
	std::cout << "\n";


    return 0;
}

