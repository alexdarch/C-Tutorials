#pragma once
#include <string>
#include <cstdlib> // for rand() and srand()

int getRandomNumber(int min, int max);


class Creature
{
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_attack;
	int m_gold;

public:
	const std::string &getName() const { return m_name; }	//if returning a reference, make sure it is const... otherwise it violates encapsulation!
	char getSymbol() const { return m_symbol; }
	int getHealth() const { return m_health; }
	int getAttack() const { return m_attack; }
	int getGold() const { return m_gold; }

public:
	Creature(const std::string &name, char sym, int hp, int att, int gold)
		:m_name{ name }, m_symbol{ sym }, m_health{ hp }, m_attack{ att }, m_gold{ gold }
	{
	}
	void reduceHealth(int damage) { m_health -= damage; }
	bool isDead() { return (m_health <= 0); }
	void addGold(int loot) { m_gold += loot; }

};

class Player : public Creature
{
private:
	int m_level = 1;
public:
	Player(const std::string &name) : Creature(name, '@', 10, 1, 0)
	{
	}
	int getLevel() const { return m_level; }
	bool hasWon() const { return (m_level >= 20); }
	void levelUp() { ++m_level;	++m_attack; }

};

class Monster : public Creature
{
public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};
private:
	struct MonsterData {
		std::string s_name;
		char s_symbol;
		int s_health;
		int s_attack;
		int s_gold;
	};
public:
	static MonsterData monsterData[MAX_TYPES]; //declared before constructor


	Monster(Type type) : Creature(monsterData[type].s_name, monsterData[type].s_symbol,
		monsterData[type].s_health, monsterData[type].s_attack, monsterData[type].s_gold)
	{

	}
	static Monster getRandomMonster() {
		return Monster(static_cast<Type>(getRandomNumber(0, MAX_TYPES - 1)));
	}

};