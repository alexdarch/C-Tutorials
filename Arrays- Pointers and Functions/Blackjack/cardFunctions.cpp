#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "BlackJack_header.h"

void incrementIfAce(const Card &value, int &aceCounter)
{
	if (value.rank == Rank::ACE)
		aceCounter++;
}

void shuffleDeck(std::array<Card, 52> &deck)
{
	for (int index = 0; index < static_cast<signed int>(deck.size()); ++index)				//deck.size() is an unsigned int
		swapCard(deck.at(index), deck.at(getRandomNumber(0, 51)));
}

void printDeck(const std::array<Card, 52> &deck)	//dont need deck[], or a pointer for std::array. Remember const and & to stop copying and to prevent changes
{
	for (const auto value : deck)
	{
		printCard(value);
		std::cout << " ";
	}
	std::cout << "\n";
}

char getPlayerChoice()
{
	std::cout << "(h) to hit, or (s) to stand: ";
	char choice;
	do
	{
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Extraction has failed due to the entry of an incorrect type or an overflow. Please enter an integer.\n";
		}
		std::cin.ignore(32767, '\n');

	} while (choice != 'h' && choice != 's');

	return choice;
}

void printCard(const Card &value)
{
	//just to make things more succinct
	using namespace Suit;
	using namespace Rank;
	using namespace std;

	switch (value.rank)
	{
	case TWO:	cout << "2";	break;
	case THREE:	cout << "3";	break;
	case FOUR:	cout << "4";	break;
	case FIVE:	cout << "5";	break;
	case SIX:	cout << "6";	break;
	case SEVEN:	cout << "7";	break;
	case EIGHT:	cout << "8";	break;
	case NINE:	cout << "9";	break;
	case TEN:	cout << "10";	break;
	case JACK:	cout << "J";	break;
	case QUEEN:	cout << "Q";	break;
	case KING:	cout << "K";	break;
	case ACE:	cout << "A";	break;
	}

	//needs to be under rank since we want JS for jack of spades etc.
	switch (value.suit)
	{
	case CLUBS:		cout << "C";	break;
	case DIAMONDS:	cout << "D";	break;
	case HEARTS:	cout << "H";	break;
	case SPADES:	cout << "S";	break;
	}
}

int getCardValue(const Card &value)
{
	using namespace Rank;

	switch (value.rank)
	{
	case TWO:	return 2;
	case THREE:	return 3;
	case FOUR:	return 4;
	case FIVE:	return 5;
	case SIX:	return 6;
	case SEVEN: return 7;
	case EIGHT: return 8;
	case NINE:	return 9;
	case TEN:	return 10;
	case JACK:	return 10;
	case QUEEN:	return 10;
	case KING:	return 10;
	case ACE:	return 11;
	}
	return 0;	//could have put this as the default case
}

void swapCard(Card &card1, Card &card2)
{
	//dont want the const here since we are changing things
	Card temp;
	temp = card1;
	card1 = card2;
	card2 = temp;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
															// evenly distribute the random number across our range
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}