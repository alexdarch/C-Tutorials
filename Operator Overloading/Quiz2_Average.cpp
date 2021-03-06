// Quiz2_Average.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>

//Write a class named Average that will keep track of the average of all integers passed to it.Use two members:
//The first one should be type int32_t, and used to keep track of the sum of all the numbers you’ve seen so far.
//The second should be of type int8_t, and used to keep track of how many numbers you’ve seen so far. You can divide them to find your average.


class Average
{
private:
	int32_t m_sum;
	int8_t m_numbers;

public:
	Average() : m_sum{ 0 }, m_numbers{ 0 }	//initialise avg variables
	{
	}

	Average& operator+=(int a)
	{
		m_sum += a;
		++m_numbers;
		return *this;
	}


	friend std::ostream& operator<<(std::ostream &out, const Average &i);
};

std::ostream& operator<<(std::ostream &out, const Average &i)
{
	out << static_cast<double>(i.m_sum) / i.m_numbers;
	return out;
}

int main()
{
	Average avg;

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy = avg;
	std::cout << copy << '\n';
    return 0;
}

