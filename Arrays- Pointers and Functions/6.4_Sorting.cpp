// 6.4_Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

const int g_length = 9;
void selectionSort(int array[g_length]);
void bubbleSort(int array[g_length]);


int main()
{

	
	int array1[g_length] = { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	selectionSort(array1);
	std::cout << "\n";
	int array2[g_length] = { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	bubbleSort(array2);

    return 0;
}

void bubbleSort(int array[g_length])
{
	for (int iteration = 0; iteration < g_length - 1; ++iteration)
	{
		int swaps = 0;
		for (int index = 0; index < g_length - 1 - iteration; ++index)
		{
			//A) Compare array element 0 with array element 1. If element 0 is larger, swap it with element 1.
			//B) Now do the same for elements 1 and 2, and every subsequent pair of elements until you hit the end of the array.At this point, the last element in the array will be sorted.
			if (array[index] > array[index + 1])
			{
				std::swap(array[index], array[index + 1]);
				swaps++;
			}

			//C) Repeat the first two steps again until the array is sorted.
		}
		if (swaps == 0)
		{
			std::cout << "\nEarly termination on iteration " << iteration << "\n";
			break;
		}
	}

	for (int index = 0; index < g_length; ++index)
		std::cout << array[index] << ' ';
}


void selectionSort(int array[g_length])
{

	// Step through each element of the array
	// (except the last one, which will already be sorted by the time we get there)
	for (int startIndex = 0; startIndex < g_length - 1; ++startIndex)
	{
		// smallestIndex is the index of the smallest element we’ve encountered this iteration
		// Start by assuming the smallest element is the first element of this iteration
		int smallestIndex = startIndex;

		// Then look for a smaller element in the rest of the array
		for (int currentIndex = startIndex + 1; currentIndex < g_length; ++currentIndex)
		{
			// If we've found an element that is smaller than our previously found smallest
			if (array[currentIndex] > array[smallestIndex])													//swap > to < to sort from min to max
				// then keep track of it
				smallestIndex = currentIndex;
		}

		// smallestIndex is now the smallest element in the remaining array
		// swap our start element with our smallest element (this sorts it into the correct place)
		std::swap(array[startIndex], array[smallestIndex]);
	}

	// Now that the whole array is sorted, print our sorted array as proof it works
	for (int index = 0; index < g_length; ++index)
		std::cout << array[index] << ' ';

}