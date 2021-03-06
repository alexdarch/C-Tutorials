// 6.3_Arrays_and_Loops.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

const int g_arrayLength = 9;


void printQ1Array(const int array[g_arrayLength]);
int getDigit(); //also checks for erronous inputs
int searchArrayAndReturnIndex(int number, const int array[g_arrayLength]);




int main()
{
	//###########################################################
	//###########################################################
	//##################  Questions 1&2 #########################


	const int array[] = { 4, 6, 7, 3, 8, 2, 1, 9, 5 };
	//const int length = sizeof(array) / sizeof(array[0]);    //made this a global variable

	int digit = getDigit();
	printQ1Array(array);
	int index = searchArrayAndReturnIndex(digit, array);
	
	if (index != -1)
		std::cout << "Yep! " << digit << " has the index: " << index << " in this array\n";
	else
		std::cout << "Sorry that digit isn't indexed in this array\n"; //this should never happen as we have error checked in getDigit()

	//###########################################################
	//###########################################################
	//###################  Question 3 ###########################

	int scores[] = { 84, 92, 76, 81, 56 };
	const int numStudents = sizeof(scores) / sizeof(scores[0]);

	int maxScore = 0; // keep track of our largest score
	int maxIndex = -1;

					  // now look for a larger score
	for (int student = 0; student < numStudents; ++student)
		if (scores[student] > maxScore)
		{
			maxScore = scores[student];
			maxIndex = student;
		}

	std::cout << "The best score was " << maxScore << '\n';
	std::cout << "The index of the best score was " << maxIndex << "\n";

    return 0;
}



int searchArrayAndReturnIndex(int number, const int array[g_arrayLength])
{
	for (int index = 0; index < g_arrayLength; ++index)
	{
		if (array[index] == number)
			return index;
	}
	return -1; //shouldnt ever happen if getDigit() works
}

void printQ1Array(const int array[g_arrayLength])
{
	for (int index = 0; index < g_arrayLength; index++)
	{
		std::cout << "The " << index << "th element of array is: " << array[index] << std::endl;
	}
}

int getDigit()
{
	// First, read in valid input from user
	int digit = 0;
	do
	{
		std::cout << "Enter a number between 1 and 9: ";
		std::cin >> digit;

		// if the user entered an invalid character
		if (std::cin.fail())
		{
			std::cin.clear(); // reset any error flags
			std::cout << "Extraction has failed due to the entry of an incorrect type or an overflow. Please enter an integer.\n";
		}

		std::cin.ignore(32767, '\n'); // ignore any extra characters in the input buffer

	} while (digit < 1 || digit > 9);

	return digit;
}