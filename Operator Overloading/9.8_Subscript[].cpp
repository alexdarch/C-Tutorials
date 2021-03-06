// 9.8_Subscript[].cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>




struct StudentGrade
{
	std::string name;
	char grade;
};


class GradeMap
{
private:
	std::vector<StudentGrade>m_map;

public:
	GradeMap()
	{
	}

	char& operator[](const std::string &identity)
	{
		for (StudentGrade &element : m_map)		//search for the student
		{
			if (element.name == identity)
				return element.grade;			//if it exists return a reference to that student so we can assign to it
			
		}

		StudentGrade i{ identity, ' ' };	//create a new student if we didnt find one
		m_map.push_back(i);		//push the anonymous object back onto the vector with the student name

		// and return the element we just added
		return m_map.back().grade;
	}

};

int main()
{
	GradeMap grades;
	grades["Joe"] = 'A';
	grades["Frank"] = 'B';
	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';


    return 0;
}

