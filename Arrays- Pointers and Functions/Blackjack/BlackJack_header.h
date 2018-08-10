#pragma once


#include <string>	//we only include things in the header if they are required for function definitions
#include <array>	//otherwise you are copying the whole header here and then twice more into the cpp files
					//so effectively <array> is being #included 3 times here (but unfortunately this is necessary)

namespace Suit
{
	enum Suit
	{
		CLUBS,
		DIAMONDS,
		HEARTS,
		SPADES,
		MAX_SUITS
	};
}

namespace Rank
{
	enum Rank
	{
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE,
		MAX_RANK
	};
}

struct Card
{
	Suit::Suit suit;
	Rank::Rank rank;
};


void printCard(const Card &value);						//prints a card e.g. "JS" if we send in value.rank = Rank::JACK and value.suit = Suit::SPADES
void printDeck(const std::array<Card, 52> &deck);		//prints the entire deck in the order of the array
void swapCard(Card &card1, Card &card2);				//swaps the contents of two cards
int getRandomNumber(int min, int max);
void shuffleDeck(std::array<Card, 52> &deck);
int getCardValue(const Card &value);
char getPlayerChoice();

void incrementIfAce(const Card &value, int &aceCounter);	//takes the current card and if it is an ace, it increments the appropriate ace counter.