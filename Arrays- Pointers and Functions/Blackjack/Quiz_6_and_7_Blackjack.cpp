// Quiz_6_and_7_Blackjack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "BlackJack_header.h"

bool playBlackjack(std::array<Card, 52> &shuffledDeck)
{
	//Initialize a pointer to the first Card named cardPtr.This will be used to deal out cards from the deck(see the hint below).
	Card *cardPtr = &shuffledDeck[0];

	int playerScore = 0;
	int dealerScore = 0;
	int playerAces = 0;		//keep track of how many aces each player has
	int dealerAces = 0;

	//The dealer gets one card to start(in real life, the dealer gets two, but one is face down so it doesn’t matter at this point).
	//The player gets two cards to start.
	incrementIfAce(*cardPtr, dealerAces);
	dealerScore += getCardValue(*cardPtr++);								//takes first card and then increments (++ is a suffix). * has higher precedence than ++
	incrementIfAce(*cardPtr, playerAces);
	playerScore += getCardValue(*cardPtr++);								
	incrementIfAce(*cardPtr, playerAces);
	playerScore += getCardValue(*cardPtr++);		

	std::cout << "\nDealer Score: " << dealerScore << "  Player Score: " << playerScore << "\n";


	while(true)
	{
		//did you bust? If so, they lose immediately (dealers edge), unless you have an ace to save yourself.
		if (playerScore > 21)
		{
			if (playerAces > 0)
			{
				std::cout << "You have an ace, so can change that to a 1 to save yourself from busting.\n";
				--playerAces;
				playerScore -= 10;
			}
			else 
			{
				std::cout << "Sorry. You have bust with a score of " << playerScore << ".\n";
				return false;	//false = player loses.
			}
		}


		std::cout << "Your current score is: " << playerScore << "\n";
		char hitOrStand = getPlayerChoice();


		if (playerScore <= 14) //have to hit
		{
			std::cout << "Sorry. Your score is 14 or below. You have to hit.\n";
			continue;	//ask the to press hit again. (Maybe force them to increment the counter?)
		}

		//stick or hit?
		if (hitOrStand == 'h')
		{
			std::cout << "You got a ";
			printCard(*cardPtr);
			std::cout << ". Add " << getCardValue(*cardPtr) << " to your score.\n";
			incrementIfAce(*cardPtr, playerAces);										//we check if the current top card is an ace and, if so, add it to the counter
			playerScore += getCardValue(*cardPtr++);
		}
		else
		{
			std::cout << "You stood on a score of " << playerScore << ". Dealers turn.\n";
			break;
		}
	}
	std::cout << "\n";	//formatting



	//The dealer repeatedly draws until they reach a score of 17 or more, at which point they stand.
	while (dealerScore < 17)
	{
		std::cout << "The dealer got a ";
		printCard(*cardPtr);
		std::cout << ". Add " << getCardValue(*cardPtr) << " to the score.\n";

		incrementIfAce(*cardPtr, dealerAces);
		dealerScore += getCardValue(*cardPtr++);
		std::cout << "The dealer's current score is: " << dealerScore << "\n";
	
		if (dealerScore > 21)		//If the dealer goes over a score of 21, they bust and the player wins immediately.
		{
			if (dealerAces > 0)
			{
				--dealerAces;
				dealerScore -= 10;
				std::cout << "The dealer's score is now: " << dealerScore << "\n";
			}
			else 
			{
				std::cout << "The dealer has busted.\n";
				true;
			}
			
		}

	}
	std::cout << "The dealer has stood.\n";


	//Otherwise, if the player has a higher score than the dealer, the player wins. Otherwise, the player loses(we’ll consider ties as dealer wins for simplicity).
	return (playerScore > dealerScore);
}



int main()
{
	std::srand(1);
	std::rand(); //call this once to discard the first value.

	//initialise deck
	std::array<Card, 52> deck; //remember to include array

	int card = 0;
	for (int cardSuit = 0; cardSuit < Suit::MAX_SUITS; ++cardSuit)
	{
		for (int cardRank = 0; cardRank < Rank::MAX_RANK; ++cardRank)
		{
			deck.at(card).suit = static_cast<Suit::Suit>(cardSuit);
			deck.at(card).rank = static_cast<Rank::Rank>(cardRank);

			++card;
		}
	}

	shuffleDeck(deck);
	std::cout << "\n";

	printDeck(deck);
	std::cout << "\n";

	bool playerWin = playBlackjack(deck);
	std::cout << "\n";
	if (playerWin)
		std::cout << "You win!\n";
	else
		std::cout << "Dealer wins!\n";

    return 0;
}

