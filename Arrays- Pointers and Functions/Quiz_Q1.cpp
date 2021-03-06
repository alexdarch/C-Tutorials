// Quiz_Q1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

namespace Item //could use enum class, but then we would have to statically cast Item::HEALTH_POTION etc.
{
	enum Item
	{
		HEALTH_POTION,
		TORCH,
		ARROWS,
		MAX_ITEMS
	};
}

int countTotalItems(const int *numOfItems)//use this form rather than int numOfItems[] to remind us that fixed arrays decay to a pointer
{
	int totItems = 0;

	for (int itemType = 0; itemType < Item::MAX_ITEMS; ++itemType) //enum keeps track of array size for us
	{
		//totItems += numOfItems[itemType];
		totItems += *(numOfItems + itemType);      //equivalent using pointer arithmatic

	}

	return totItems;
}


int main()
{
	int numOfItems[Item::MAX_ITEMS]{ 2, 5, 10 };

	std::cout << "The player has " << countTotalItems(numOfItems) << " items in total.\n";

    return 0;
}

