// Quiz3_Monster_Generator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdlib> // for std::and() and std::srand()
#include <ctime> // for std::time()


class Monster
{
public:
	enum MonsterType
	{
		DRAGON,
		GOBLIN,
		OGRE,
		ORC,
		SKELETON,
		TROLL,
		VAMPIRE,
		ZOMBIE,
		MAX_MONSTER_TYPES
	};

private:
	MonsterType m_type;
	std::string m_name;
	std::string m_roar;
	int m_hitPoints;

	std::string getTypeString() const		//needs to be constant to be compatible with getTypeString().... cant be called otherwise!
	{
		switch (m_type) 
		{
			case DRAGON:	return "Dragon";
			case GOBLIN:	return "Goblin";
			case OGRE:		return "Ogre";
			case ORC:		return "Orc";
			case SKELETON:	return "Skeleton";
			case TROLL:		return "Troll";
			case VAMPIRE:	return "Vampire";
			case ZOMBIE:	return "Zombie";
			default:		return "ERROR: Not a monster type";
		}
	}


public:
	Monster(const MonsterType &type, const std::string &name, const std::string &roar, const int &hitPoints)
		:m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
	{

	}
	void print() const //for some reason we put the const here if the function isnt changing anything (this makes it compatible with non-const objects)
	{
		std::cout << m_name << " the " << this->getTypeString() << " has " << m_hitPoints << " HP and says " << m_roar << ".\n";				//this -> is equivalent to (*this).getTypeString()... but that looks ugly
	}		//dont actually need the "this" but, it makes it explicit that the m_type that getTypeString() is using is the same object.


	

};

class MonsterGenerator 
{
private:
	static int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
																					 // evenly distribute the random number across our range
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

public:
	static Monster generateMonster()
	{
		Monster::MonsterType type = static_cast<Monster::MonsterType>(getRandomNumber(0, Monster::MAX_MONSTER_TYPES - 1));
		int hp = getRandomNumber(1, 100);

		static std::string s_names[6]{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
		static std::string s_roars[6]{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*" };

		return Monster(type, s_names[getRandomNumber(0, 5)], s_roars[getRandomNumber(0, 5)], hp);	//we can just return an anonymous monster object.
	}

};

//. This should return a Monster. For now, make it return anonymous Monster(Monster::SKELETON, “Bones”, “*rattle*”, 4);


int main()
{
	std::srand(static_cast<unsigned int>(time(0)));
	std::rand();
	Monster m = MonsterGenerator::generateMonster();
	m.print();

    return 0;
}

