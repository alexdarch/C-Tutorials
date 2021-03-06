// 6.9a_Dynamic_Arrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

void selectionSort(std::string *names, int length)
{
	//Hint : std::string supports comparing strings via the comparison operators < and >
	for (int startIndex = 0; startIndex < length; ++startIndex)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// If the current element is smaller than our previously found smallest
			if (names[currentIndex] < names[smallestIndex])
				// This is the new smallest number for this iteration
				smallestIndex = currentIndex;
		}

		// Swap our start element with our smallest element
		std::swap(names[startIndex], names[smallestIndex]);
	}

}


int main()
{
	//*Asks the user how many names they wish to enter.
	int numOfNames = 0;
	std::cout << "how many names do you wish to enter? ";
	std::cin >> numOfNames;

	//Hint : Use a dynamic array of std::string to hold the names.
	
	//* Asks the user to enter each name.
	std::string *names = new std::string[numOfNames];

	for (int i = 0; i < numOfNames; i++)
	{
		std::cout << "Enter name #" << i + 1 << ": ";
		std::cin >> names[i];
	}

	//sort the array of names
	selectionSort(names, numOfNames);

	//* Prints the sorted list of names.
	for (int i = 0; i < numOfNames; i++)
	{
		std::cout << "Name #" << i + 1 << " is " << names[i] << "\n";
	}


	delete[] names; //DO NOT FORGET THIS!!!

    return 0;
}