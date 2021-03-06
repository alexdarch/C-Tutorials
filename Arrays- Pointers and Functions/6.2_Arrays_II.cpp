// 6.2_Arrays_II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

namespace Animals
{
	enum Animals
	{
		CHICKEN,
		DOG,
		CAT,
		ELEPHANT,
		DUCK,
		SNAKE,
		MAX_ANIMALS
	};
}


int main()
{
	double highTemp[365]{ 0.0 };  //uniform initialisation is preferred (omit the '=').

	int numberOfLegs[Animals::MAX_ANIMALS]{ 2, 4, 4, 4, 2, 0 };
	std::cout << "An elephant has " << numberOfLegs[Animals::ELEPHANT] << " legs.\n";

    return 0;
}

