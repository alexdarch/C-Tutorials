// Quiz3_IntArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>

//Write your own integer array class named IntArray from scratch (do not use std::array or std::vector).
//Users should pass in the size of the array when it is created, and the array should be dynamically allocated.
//Use assert statements to guard against bad data.
//Create any constructors or overloaded operators needed to make the following program operate correctly:

class IntArray
{
private:
	int m_length = 0;
	int *m_arr = nullptr;	//set default value as a pointer with no address (that holds a value of type int)

public:
	IntArray(int length) : m_length{ length }		//default constuctor
	{
		assert(m_length > 0 && "Length is less than zero");
		m_arr = new int[m_length] { 0 };
	}

	IntArray(const IntArray &orig) :	//deep copy constructor
		m_length{ orig.m_length }	//we cant do m_arr { orig.m_arr } here because it is a dynamic array so we need to do a deep copy
	{
		m_arr = new int[m_length];	//allocate a new dynamic array
		for (int index = 0; index < orig.m_length; index++)
			m_arr[index] = orig.m_arr[index];
	}

	~IntArray()
	{
		delete[] m_arr;
	}

	int& operator[](const int index)
	{
		assert(index >= 0 && index < m_length && "Outside of array bounds");
		return m_arr[index];
	}

	IntArray& operator=(const IntArray &arr1)
	{
		//because this is a member function, *this is the object that we are assigning to

		if (this == &arr1)	//if we are trying to self assign, then both *this and arr1 are pointing to the same address (if it is dynamic memory)
			return *this;	//so we need to just return *this before we delete[] which would dissalow us to copy things like arr1.m_array to this->m_array (because *this is now a dangling pointer)

		delete[] m_arr;		//so we delete the contents of *this, so that we dont have things like index's outside of our assigned length (memory leaks)

		m_length = arr1.m_length;
		m_arr = new int[m_length];	//allocate a new array
		for (int index = 0; index < arr1.m_length; index++)
			m_arr[index] = arr1.m_arr[index];

		return *this;
	}

	friend std::ostream& operator<<(std::ostream &out, const IntArray &arr);

};


std::ostream& operator<<(std::ostream &out, const IntArray &arr)
{
	for (int index = 0; index < arr.m_length; index++)
		out << arr.m_arr[index] << " ";

	return out;
}


IntArray fillArray()
{
	IntArray a(5);
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a = fillArray();
	std::cout << a << '\n';

	IntArray b(1);
	a = a;
	b = a;

	std::cout << b << '\n';

	return 0;
}