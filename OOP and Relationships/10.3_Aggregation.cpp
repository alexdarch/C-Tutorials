// 10.3_Aggregation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

class Teacher
{
private:
	std::string m_name;

public:
	Teacher(std::string name) : m_name{ name } 
	{
	}

	std::string getName() { return m_name; }
	
};

class Department
{
private:
	std::vector<Teacher*>m_teachers;

public:
	Department(Teacher *teacher = nullptr) 
	{
		if(teacher)				//if the pointer isnt a null pointer then push
			m_teachers.push_back(teacher);
	}

	void add(Teacher *teacher)
	{
		if(teacher)				//only add if it isnt a null pointer
			m_teachers.push_back(teacher);
	}
	void printSizeAndCapicity() { std::cout << "Length: " << m_teachers.size() << ", Capacity: " << m_teachers.capacity() << "\n"; }

	friend std::ostream& operator<<(std::ostream &out, const Department &dpt)
	{
		out << "Department: ";
		for (unsigned int index = 0; index < dpt.m_teachers.size(); ++index)
		{
			out << dpt.m_teachers.at(index)->getName();
			out << " ";
		}

		out << "\n";
		return out;
	}
};


int main()
{

	// Create a teacher outside the scope of the Department
	Teacher *t1 = new Teacher("Bob"); // create a teacher
	Teacher *t2 = new Teacher("Frank");
	Teacher *t3 = new Teacher("Beth");

	{
		// Create a department and use the constructor parameter to pass
		// the teacher to it.
		Department dept; // create an empty Department
		dept.add(t1);
		dept.add(t2);
		dept.add(t3);

		dept.printSizeAndCapicity();

		std::cout << dept;

	} // dept goes out of scope here and is destroyed

	std::cout << t1->getName() << " still exists!\n";
	std::cout << t2->getName() << " still exists!\n";
	std::cout << t3->getName() << " still exists!\n";

	delete t1;
	delete t2;
	delete t3;

    return 0;
}

