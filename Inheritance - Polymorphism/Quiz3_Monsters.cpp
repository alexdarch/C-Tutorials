// Quiz3_Monsters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Creatures.h"	//also includes, string, cstdlib, getRandomNumber();
#include <iostream>
#include <ctime> // for time()
std::string setName();
bool Fight();

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]	//our lookup table is outside the class, for convenience
{
	{"dragon", 'D', 20, 4, 100},
	{"orc", 'o', 4, 2, 25},
	{"slime", 's', 1, 1, 10}
};
bool attackMonster(Player &p, Monster &m)
{
	// handles the player attacking the monster, including leveling up.
	bool monsterAlive = true;
	m.reduceHealth(p.getAttack());
	std::cout << "You hit the " << m.getName() << " for " << p.getAttack() << " damage.\n";
	if (m.isDead())
	{
		p.addGold(m.getGold());
		p.levelUp();
		std::cout << "... and killed it. You are now level " << p.getLevel() << "\n";
		monsterAlive = false;
	}

	return monsterAlive;
}
bool attackPlayer(Player &p, Monster &m)
{
	//handles the monster attacking the player
	bool playerAlive = true;
	p.reduceHealth(m.getAttack());
	std::cout << "The " << m.getName() << " hit you for " << m.getAttack() << " damage.\n";
	if (p.isDead()) {
		playerAlive = false;
		std::cout << "... and killed you.\n";
	}
		

	return playerAlive;
}
bool fightMonster(Player &p, Monster &m)	//by reference because we want to change the values of these
{
	//handles the fight between the Player and a single Monster, 
	//including asking the player what they want to do, 
	//handling the run or fight cases.
	bool fight;
	bool successfulFlee = false;
	bool playerAlive = true;
	bool monsterAlive = true;

	do {
		std::cout << "here again\n";
		fight = Fight();	//get player's choice
		if (fight)
		{
			monsterAlive = attackMonster(p, m);
			//check if the monster has died return if so
			if(monsterAlive)
				playerAlive = attackPlayer(p, m);
		}
		else
		{
			successfulFlee = static_cast<bool>(getRandomNumber(0, 1));
			if (!successfulFlee)	//if you fail to flee, you get attacked
			{
				std::cout << "You failed to flee.\n";
				playerAlive = attackPlayer(p, m);		//and then you go back to the start of the loop
			}
			else std::cout << "You successfully fled.\n";
		}

		
		//must return if (player && monster) == false, i.e. one of them is dead
		//must also return if (!flee && alive) == false
		//only continue if both alive and unsuccessful flee
	} while (!successfulFlee && (playerAlive && monsterAlive));

	//if the player fled or won then theyre alive and can fight again
	//if the player died then you lose sadly
	return playerAlive; 
}



int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	Player player(setName());	//initialise the player
	bool alive = true;
	while (alive) 
	{
		Monster mon = Monster::getRandomMonster();
		std::cout << "you have encountered a " << mon.getName() << " (" << mon.getSymbol() << ").\n";
		alive = fightMonster(player, mon);	//returns playerAlive
	
		if (!alive)
		{
			std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << "gold.\n";
			std::cout << "Too bad you can't take it with you!\n";
		}
		if (player.hasWon()) {
			std::cout << "You won the game with " << player.getGold() << " gold!\n";
			break;
		}
	}
	
	return 0;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
																				 // evenly distribute the random number across our range
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
bool Fight() 
{
	char action;
	do
	{
		std::cout << "(R)un or (F)ight: ";
		std::cin >> action;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Extraction has failed due to entry of an incorrect type (i.e. not a char) or an overflow.";
		}
		std::cin.ignore(32767, '\n');

	} while (action != 'R' && action != 'r' && action != 'F' && action != 'f');
	return (action == 'F' || action == 'f');	//return true if player wants to fight
}
std::string setName()
{
	std::string name;
	do
	{
		std::cout << "Enter your name: ";
		std::cin >> name;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Extraction has failed due to the entry of an incorrect type or an overflow. Please enter a string (can't anything be a string?).\n";
		}
		std::cin.ignore(32767, '\n');
	} while (name.length() < 0 || name.length() > 28);	//player name has to be within 0 and 28 characters

	std::cout << "Welcome, " << name << "\n";
	return name;
}