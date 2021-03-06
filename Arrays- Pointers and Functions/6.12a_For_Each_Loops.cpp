// 6.12a_For_Each_Loops.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>


int main()
{
	std::string names[] = { "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

	bool cont = true;
	while (cont)
	{
		std::string name;
		std::cout << "Enter a name: ";
		std::cin >> name;
		bool found = false;

		for (const auto &person : names)
		{
			if (person == name)
			{
				found = true;
				break;
			}
		}

		if (found == false)
			std::cout << name << " was not found.\n";
		else
			std::cout << name << " was found.\n";


		char letter;
		std::cout << "Do you want to try again (y / any other key) ? ";
		std::cin >> letter;
		if (letter == 'y')
			cont = true;
		else
			cont = false;
	}

    return 0;
}

