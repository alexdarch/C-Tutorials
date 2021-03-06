// Quiz_Q2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

struct Student
{
	std::string name;
	int grade;
};

void swap(Student &stud1, Student &stud2)
{
	Student temp;							//swap using a temporary student
	temp = stud1;
	stud1 = stud2;
	stud2 = temp;
}

void getStudents(Student *details, int num) 
{
	for (int index = 0; index < num; ++index)
	{
		std::cout << "Enter student #" << index + 1 << "'s name: ";
		std::cin >> details[index].name;
		std::cout << "Enter student #" << index + 1 << "'s grade (1-100): ";
		std::cin >> details[index].grade;
	}
}

void sortStudents(Student *details, int num)
{
	//selection sort

	for (int startIndex = 0; startIndex < num; ++startIndex)
	{
		int bestGradeIndex = startIndex;

		for (int currentIndex = startIndex + 1; currentIndex < num; ++currentIndex)
		{
			if (details[currentIndex].grade > details[bestGradeIndex].grade)
			{
				bestGradeIndex = currentIndex;
			}
		}

		swap(details[bestGradeIndex], details[startIndex]);

		//print what is happening each sort
		std::cout << "\nNew order: \n";
		for (int index2 = 0; index2 < num; index2++)
		{
			std::cout << details[index2].name << "'s grade is: " << details[index2].grade << "       ";
		}

		std::cout << "\n";
	}

}

int main()
{
	int number;
	std::cout << "Number of Students: ";
	std::cin >> number;

	Student *details = new Student[number];
	getStudents(details, number);

	sortStudents(details, number);

	for (int index = 0; index < number; index++)
	{
		std::cout << details[index].name << "'s grade is: " << details[index].grade << "\n";
	}

	delete[] details; //dont forget to delete memory


    return 0;
}

