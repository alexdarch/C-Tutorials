#pragma once
#include <cassert>
#include <initializer_list>	//for a constructor that takes an initilizer list

class IntArray
{
private:
	int m_length;	
	int *m_data;	//want to be able to resize so dynamic allocation

public:
	IntArray() : m_length{ 0 }, m_data{ nullptr }	//default constructor constructs an empty array
	{
	}
	IntArray(int length) : m_length{ length }	//constructor to allocate an empty array with specified length
	{
		assert(m_length >= 0);

		if (length > 0)
			m_data = new int[m_length] {0};	//initialise array with garbage
		else
			m_data = nullptr;
	}
	IntArray(const std::initializer_list<int> &list) : IntArray( list.size() )	//what if we want to initialise with a list? Remember to call the !=0 length constructor first
	{
		int count = 0;
		for (auto &element : list)
		{
			m_data[count] = element;
			++count;
		}
	}

	~IntArray() { delete[] m_data; }	//destructor that auto cleans up
	void erase()
	{
		delete[] m_data;
		m_data = nullptr;	//after we erase the data, we cant just leave it pointing to deallocated memory
		m_length = 0;
	}

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length && "Index is out of bounds");
		return m_data[index];
	}
	int getLength() { return m_length;}

	void reallocate(int newLength)	//quickly deletes everything and then resizes
	{
		erase();
		if (newLength <= 0)	//if we are setting our new length to zero, might as well return here since erase has set m_data = nullptr anyway
			return;

		m_data = new int[newLength];
		m_length = newLength;
	}

	void resize(int newLength)	//slowly keeps everything and then resizes
	{
		if (newLength == m_length)	//the "do nothing" failsafe
			return;

		if (newLength <= 0)	//the 2nd failsafe
		{
			erase();
			return;
		}
		
		// Now we can assume newLength is at least 1 element.  This algorithm
		// works as follows: First we are going to allocate a new array.  Then we
		// are going to copy elements from the existing array to the new array.
		// Once that is done, we can destroy the old array, and make m_data
		// point to the new array.

		int *data = new int[newLength];		//allocate new array
		if (m_length > 0)
		{
			int elementsToCopy = (newLength > m_length) ? m_length : newLength;	//get the smaller of the two

			for (int index = 0; index < elementsToCopy; ++index)	//and copy the old ones into the new ones up to the right length
				data[index] = m_data[index];	//if newLength < m_length then we just copy m_data's elements up to element (newLength - 1) of the old array
												//if newLength > m_length then we copy all of m_data to the new array, and leave the remaining values as unallocated
		}

		delete[] m_data;	//now we can delete the old array
		m_length = newLength;	
		m_data = data;		//and set m_data to point to the same address as data. Because data was dynamically allocated, it won't be destroyed when out of scope (the variable will, but not the data)
	}

	void insertBefore(int value, int index)
	{
		// Sanity check our index value
		assert(index >= 0 && index <= m_length);

		int *data = new int[m_length + 1];	//create a new array one larger than before

		for (int before = 0; before < index; before++)
			data[before] = m_data[before];

		data[index] = value;

		for (int after = index; after < m_length; after++)
			data[after + 1] = m_data[after];

		delete[] m_data;
		m_data = data;
		m_length++;
	}

	void remove(int index)
	{
		// Sanity check our index value
		assert(index >= 0 && index < m_length);

		// If this is the last element in the array, set the array to empty and bail out
		if (m_length == 1)
		{
			erase();
			return;
		}

		// First create a new array one element smaller than the old array
		int *data = new int[m_length - 1];

		// Copy all of the elements up to the index
		for (int before = 0; before < index; ++before)
			data[before] = m_data[before];

		// Copy all of the values after the removed element
		for (int after = index + 1; after < m_length; ++after)
			data[after - 1] = m_data[after];

		// Finally, delete the old array, and use the new array instead
		delete[] m_data;
		m_data = data;
		--m_length;
	}

	// A couple of additional functions just for convenience
	void insertAtBeginning(int value) { insertBefore(value, 0); }
	void insertAtEnd(int value) { insertBefore(value, m_length); }

};