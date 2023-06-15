/*******************************************************************************
* Programmer: Cole Hartman													  *
* Date:	4/19/23																  *
* Programming Assignment: PA 7: 5 card draw poker							  *
* Description:	This file houses the preproccesor directives, structs, and prototypes*
******************************************************************************/

#ifndef LIBRARY_H
#define LIBRARY_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct card
{

	int index_face;
	int index_suit;

}Card;

typedef struct hand
{
	Card arr_of_cards[5];
	int FaceTable[13];
	int SuitTable[4];
	int Player;
	int Score;
	int Wins;

	int HighCardValue;
	int HighCard;
	int Pair;
	int TwoPairs;
	int ThreeOfAKind;
	int Straight;
	int Flush;
	int FullHouse;
	int FourOfAKind;
	int StraightFlush;

}Hand;

/******************************************************************************
*Function: PrintFileContents
*Description: Takes in a file name and prints the contents
*Input: filename
*Output: void
******************************************************************************/
void PrintFileContents(const char* filename);

/******************************************************************************
*Function: shuffle
*Description: initializes the 2d deck array with random numbers 1-52. each card has a row and collum that corresponds to a face and suit
*Input: int wDeck[][13]
*Output: void
******************************************************************************/
void shuffle(int wDeck[][13]);

/******************************************************************************
*Function: deal
*Description: fills the arr_of_cards array with 5 cards
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer);

/******************************************************************************
*Function: print_rules
*Description: Prints the rules of poker
*Input: void
*Output: void
******************************************************************************/
void print_rules(void);

/******************************************************************************
*Function: FaceFrequencyTable
*Description: Creates a frequency array for the hand based off each cards face
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void FaceFrequencyTable(Hand* PlayerOrDealer);

/******************************************************************************
*Function: SuitFrequencyTable
*Description: Creates a frequency array for the hand based off each cards suit
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void SuitFrequencyTable(Hand* PlayerOrDealer);

/******************************************************************************
*Function: HighCard
*Description: Checks the hand for a high card
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void HighCard(Hand* PlayerOrDealer);

/******************************************************************************
*Function: TieHighCard
*Description: If the player and dealer tie with a high card, search for the next card in their hand and set that to the high card value
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void TieHighCard(Hand* PlayerOrDealer);

/******************************************************************************
*Function: OneOrTwoPairs
*Description: Check hand for one or two pairs
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void OneOrTwoPairs(Hand* PlayerOrDealer);

/******************************************************************************
*Function: ThreeOrFourOfAKind
*Description: Check hand for three or four of a kind
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ThreeOrFourOfAKind(Hand* PlayerOrDealer);

/******************************************************************************
*Function: FullHouse
*Description: Check the hand for a full house
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void FullHouse(Hand* PlayerOrDealer);

/******************************************************************************
*Function: Flush
*Description: Check the hand for a flush
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void Flush(Hand* PlayerOrDealer);

/******************************************************************************
*Function: Straight
*Description: Check the hand for a straight
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void Straight(Hand* PlayerOrDealer);

/******************************************************************************
*Function: StraightFlush
*Description: Check the hand for a straight flush
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void StraightFlush(Hand* PlayerOrDealer);

/******************************************************************************
*Function: AIRedraw
*Description: Allow the dealer to evaluate their deck and redraw specific cards to increase the chances of the best possible hand
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Dealer, int* CardCount
*Output: voidS
******************************************************************************/
void AIRedraw(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Dealer, int* CardCount);

/******************************************************************************
*Function: DrawOneCard
*Description: Draws one card from the deck that hasn't been used and replaces it with the desired card in the hand
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer, int* CardCount, int WhichCard
*Output: void
******************************************************************************/
void DrawOneCard(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer, int* CardCount, int WhichCard);

/******************************************************************************
*Function: PrintHand
*Description: Prints the hand
*Input: Hand* PlayerOrDealer, const char* wFace[], const char* wSuit[]
*Output: void
******************************************************************************/
void PrintHand(Hand* PlayerOrDealer, const char* wFace[], const char* wSuit[]);

/******************************************************************************
*Function: AskToRedraw
*Description: Asks the player if they want to redraw, if yes, it redraws a desired amount of specific cards from 1-3
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Player, int* CardCount
*Output: void
******************************************************************************/
void AskToRedraw(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Player, int* CardCount);

/******************************************************************************
*Function: ComputeScore
*Description: Using the values from the combo variables in the struct to determine what the dealer or players ending score should be
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ComputeScore(Hand* PlayerOrDealer);

/******************************************************************************
*Function: CompareScore
*Description: Compares the score of the Player and Dealer and outputs the result to the log file
*Input: Hand* Player, Hand* Dealer, FILE* log_file
*Output: void
******************************************************************************/
void CompareScore(Hand* Player, Hand* Dealer, FILE* log_file);

/******************************************************************************
*Function: ResetCombos
*Description: Resets all the combo variables in the struct
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ResetCombos(Hand* PlayerOrDealer);


#endif

