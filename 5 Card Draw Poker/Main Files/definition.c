#include "library.h"

/******************************************************************************
*Function: PrintFileContents
*Description: Takes in a file name and prints the contents
*Input: filename
*Output: void
******************************************************************************/
void PrintFileContents(const char* filename)
{
	////ALL ASCII ART IS FROM https://patorjk.com/software/taag/#p=display&f=Doom&t=RULES ///////////////////////////////////////////

	FILE* file;
	char line[100];

	file = fopen(filename, "r");

	while (fgets(line, sizeof(line), file) != NULL)
	{
		printf("%s", line);
	}

	fclose(file);
}

/******************************************************************************
*Function: shuffle
*Description: initializes the 2d deck array with random numbers 1-52. each card has a row and collum that corresponds to a face and suit
*Input: int wDeck[][13]
*Output: void
******************************************************************************/
//Randomly generates a 2d array of cards
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/******************************************************************************
*Function: deal
*Description: fills the arr_of_cards array with 5 cards
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer
*Output: void
******************************************************************************/
/* deal cards in deck */
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer) 
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */


	if (PlayerOrDealer->Player == 1) //Dealer
	{
		system("cls");
		//Deals cards 1-5 (5 cards) to Dealer
		for (card = 1; card <= 5; card++)
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						PlayerOrDealer->arr_of_cards[card - 1].index_face = column;
						PlayerOrDealer->arr_of_cards[card - 1].index_suit = row;
						
					}
				}
			}
		}
	}
	else if (PlayerOrDealer->Player == 2) //Player
	{
		system("cls");
		printf("YOUR HAND:\n\n");
		//Deal cards 6-10 (5 cards) to Player
		for (int card = 6, i = 0; card <= 10; card++, i++)
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						PlayerOrDealer->arr_of_cards[i].index_face = column;
						PlayerOrDealer->arr_of_cards[i].index_suit = row;

						printf("%s of ", wFace[PlayerOrDealer->arr_of_cards[i].index_face]);
						printf("%s\n", wSuit[PlayerOrDealer->arr_of_cards[i].index_suit]);
					}
				}
			}
		}
	}
}

/******************************************************************************
*Function: print_rules
*Description: Prints the rules of poker
*Input: void
*Output: void
******************************************************************************/
void print_rules(void)
{
	PrintFileContents("RULES.txt");
	printf("\nRULES OF POKER\n\n\n");
	printf("On betting rounds you can:\n   - Check: Dont bet(Once a bet is made, check is no longer an option\n   - Call : You match the previous players bet\n   - Raise : You bet more then the previous bet\n   - Fold : Discarding all cards for this round\n\n");
	printf("Each player places the ante into the pot, the ante amount is predetermined\nFive cards are dealt to each player\n\n");
	printf("ROUND 1: All players make their first move\n");
	printf("ROUND 2: After players who havent folded are done betting, everyone can discard up to 3 unwanted cards from their hand and the dealer will deal the same number of cards back\n");
	printf("ROUND 3: Bet again, there is no chance to discard cards on this round\n");
	printf("ROUND 4: Everyone who hasn’t folded reveals their hand\n\nObjective: To win chips by being the only player that did not fold, or having the highest ranking hand between the players who did not fold");
}

/******************************************************************************
*Function: FaceFrequencyTable
*Description: Creates a frequency array for the hand based off each cards face
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void FaceFrequencyTable(Hand* PlayerOrDealer)
{
	//RESET FACE TABLE
	for (int face = 0; face < 13; face++) //Check for each face card (1-King)
	{
		PlayerOrDealer->FaceTable[face] = -1;
	}
		
	for (int card = 0; card < 5; card++) //Look at each card
	{
 		for (int face = 0; face < 13; face++) //Check for each face card (1-King)
		{
			if (PlayerOrDealer->arr_of_cards[card].index_face == face)
			{
				PlayerOrDealer->FaceTable[face] += 1;
			}
		}
	}


}

/******************************************************************************
*Function: SuitFrequencyTable
*Description: Creates a frequency array for the hand based off each cards suit
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void SuitFrequencyTable(Hand* PlayerOrDealer)
{
	//RESER SUIT TABLE

	for (int suit = 0; suit < 4; suit++) //Check for each face card (1-King)
	{
		PlayerOrDealer->SuitTable[suit] = -1;
	}

	for (int card = 0; card < 5; card++) //Look at each card
	{
		for (int suit = 0; suit < 4; suit++) //Check for each face card (1-King)
		{
			if (PlayerOrDealer->arr_of_cards[card].index_suit == suit)
			{
				PlayerOrDealer->SuitTable[suit] += 1;
			}
		}
	}


}

/******************************************************************************
*Function: HighCard
*Description: Checks the hand for a high card
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void HighCard(Hand* PlayerOrDealer)
{
	//If there are no other combinations
	if (PlayerOrDealer->Flush != 1 && PlayerOrDealer->FourOfAKind != 1 && PlayerOrDealer->FullHouse != 1 && PlayerOrDealer->Pair != 1 && PlayerOrDealer->Straight != 1 && PlayerOrDealer->StraightFlush != 1 && PlayerOrDealer->ThreeOfAKind != 1 && PlayerOrDealer->TwoPairs != 1)
	{
		PlayerOrDealer->HighCardValue = 0;

		for (int i = 0; i < 5; i++) //Loop through arr_of_cards
		{
			if (PlayerOrDealer->arr_of_cards[i].index_face > PlayerOrDealer->HighCardValue)
			{
				PlayerOrDealer->HighCardValue = PlayerOrDealer->arr_of_cards[i].index_face;
			}

		}
		//Search for ACE
		for (int i = 0; i < 5; i++) //Loop through arr_of_cards again
		{
			if (PlayerOrDealer->arr_of_cards[i].index_face == 0)
			{
				PlayerOrDealer->HighCardValue = 15;
			}

		}

	}


}

/******************************************************************************
*Function: TieHighCard
*Description: If the player and dealer tie with a high card, search for the next card in their hand and set that to the high card value
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void TieHighCard(Hand* PlayerOrDealer)
{
	int CurrentHighCard = PlayerOrDealer->HighCardValue;
	PlayerOrDealer->HighCardValue = 0;

	//If there is a card 
	for (int i = 0; i < 5; i++) //Loop through arr_of_cards
	{
		if (PlayerOrDealer->arr_of_cards[i].index_face > PlayerOrDealer->HighCardValue && PlayerOrDealer->arr_of_cards[i].index_face != CurrentHighCard)
		{
			PlayerOrDealer->HighCardValue = PlayerOrDealer->arr_of_cards[i].index_face;
		}

	}
	
}

/******************************************************************************
*Function: OneOrTwoPairs
*Description: Check hand for one or two pairs
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void OneOrTwoPairs(Hand* PlayerOrDealer)
{
	int PairNum = 0, PairIndex = 0;
	for (int i = 0; i < 13; i++)
	{
		if (PlayerOrDealer->FaceTable[i] == 1)
		{
			PairNum += 1;
			PairIndex = i; 
		}

	}
	if (PairNum == 1)
	{
		PlayerOrDealer->Pair = 1; 

		
	}
	if (PairNum == 2)
	{
		PlayerOrDealer->TwoPairs = 1; 

	}

}

/******************************************************************************
*Function: ThreeOrFourOfAKind
*Description: Check hand for three or four of a kind
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ThreeOrFourOfAKind(Hand* PlayerOrDealer)
{
	for (int i = 0; i < 13; i++)
	{
		if (PlayerOrDealer->FaceTable[i] == 2)
		{
			PlayerOrDealer->ThreeOfAKind = 1;
		}
		if (PlayerOrDealer->FaceTable[i] == 3)
		{
			PlayerOrDealer->FourOfAKind = 1;

		}

	}
}

/******************************************************************************
*Function: FullHouse
*Description: Check the hand for a full house
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void FullHouse(Hand* PlayerOrDealer)
{
	int combo_count = 0;
	for (int i = 0; i < 13; i++)
	{
		if (PlayerOrDealer->FaceTable[i] == 1)
		{
			combo_count += 1;
		}
		if (PlayerOrDealer->FaceTable[i] == 2)
		{
			combo_count += 1;
		}

	}
	if (combo_count == 2)
	{
		PlayerOrDealer->FullHouse = 1;
	}
}

/******************************************************************************
*Function: Flush
*Description: Check the hand for a flush
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void Flush(Hand* PlayerOrDealer)
{
	for (int i = 0; i < 4; i++)
	{
		if (PlayerOrDealer->SuitTable[i] == 4)
		{
			PlayerOrDealer->Flush = 1;
		}
	}
	
}

/******************************************************************************
*Function: Straight
*Description: Check the hand for a straight
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void Straight(Hand* PlayerOrDealer)
{
	int consecutive_card_count = 0, consecutive_card_count_2 = 0;

	//CHECK FOR 5 CARDS IN A ROW
	for (int i = 0; i < 13; i++)
	{
		if (PlayerOrDealer->FaceTable[i] == 0)
		{
			consecutive_card_count += 1;
		}
		if (PlayerOrDealer->FaceTable[i] != 0)
		{
			consecutive_card_count = 0;
		}
		if (consecutive_card_count == 5)
		{
			PlayerOrDealer->Straight = 1;
		}
	}
	//CHECK FOR 5 CARDS IN A ROW IF ACE IS HIGH (9, 10, 11, 12, 0) or (ten, jack, queen, king, ace)
	for (int i = 9; i < 13; i++)
	{
		if (PlayerOrDealer->FaceTable[i] == 0) //check 9 - 12
		{
			consecutive_card_count_2 += 1;
		}
		if (PlayerOrDealer->FaceTable[i] != 0) 
		{
			consecutive_card_count_2 = 0;
		}
	}
	if (PlayerOrDealer->FaceTable[0] == 0) //check 0
	{
		consecutive_card_count_2 += 1;
	}
	if (consecutive_card_count_2 == 5)
	{
		PlayerOrDealer->Straight = 1;
	}
	
}

/******************************************************************************
*Function: StraightFlush
*Description: Check the hand for a straight flush
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void StraightFlush(Hand* PlayerOrDealer)
{
	if (PlayerOrDealer->Straight == 1 && PlayerOrDealer->Flush == 1)
	{
		PlayerOrDealer->StraightFlush = 1;
	}



}

/******************************************************************************
*Function: AIRedraw
*Description: Allow the dealer to evaluate their deck and redraw specific cards to increase the chances of the best possible hand
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Dealer, int* CardCount
*Output: voidS
******************************************************************************/
void AIRedraw(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Dealer, int* CardCount)
{
	int WhichCard = 0;

	//Check for combos
	OneOrTwoPairs(Dealer);
	ThreeOrFourOfAKind(Dealer);
	FullHouse(Dealer);
	Flush(Dealer);
	Straight(Dealer); 
	StraightFlush(Dealer); 
	HighCard(Dealer);

	//Evaluate hand and redraw
	if (Dealer->StraightFlush == 1)
	{

	}
	else if (Dealer->FullHouse == 1)
	{

	}
	else if (Dealer->Flush == 1)
	{

	}
	else if (Dealer->Straight == 1)
	{

	}
	else if (Dealer->FourOfAKind == 1) //FOUR OF A KIND
	{
		for (int i = 0; i < 13; i++) //Loop through FaceTable
		{
			if (Dealer->FaceTable[i] == 3) //Once you find 4 of one kind...
			{

				for (int a = 0; a < 5; a++) //Loop through arr_of_cards
				{
					if (Dealer->arr_of_cards[a].index_face != i) //Once you find a card 
					{
						WhichCard = a;
						DrawOneCard(wDeck, wFace, wSuit, Dealer, CardCount, WhichCard);
					}
				}
			}

		}

	}
	else if (Dealer->ThreeOfAKind == 1) //3 OF A KIND
	{
		for (int i = 0; i < 13; i++) //Loop through FaceTable
		{
			if (Dealer->FaceTable[i] == 2) //Once you find 3 of one kind...
			{

				for (int a = 0; a < 5; a++) //Loop through arr_of_cards
				{
					if (Dealer->arr_of_cards[a].index_face != i) //Once you find a card 
					{
						WhichCard = a;
						DrawOneCard(wDeck, wFace, wSuit, Dealer, CardCount, WhichCard);
						
					}
				}
			}

		}

	}
	else if (Dealer->TwoPairs == 1) //TWO PAIRS
	{
		int LoopCount = 0, Pair1 = 0, Pair2 = 0;

		for (int i = 0; i < 13; i++) //Loop through FaceTable
		{
			if (Dealer->FaceTable[i] == 1) //Once you find a pair
			{

				if (LoopCount == 0)
				{
					Pair1 = i;
					LoopCount += 1;
				}
				if (LoopCount == 1);
				{
					Pair2 = i;
				}

			}

		}
		for (int a = 0; a < 5; a++) //Loop through arr_of_cards
		{
			if (Dealer->arr_of_cards[a].index_face != Pair1 || Dealer->arr_of_cards->index_face != Pair2) //Once you find a card 
			{
				
				WhichCard = a;
				DrawOneCard(wDeck, wFace, wSuit, Dealer, CardCount, WhichCard);
			}
		}
		

	}
	else if (Dealer->Pair == 1) //PAIR
	{
		for (int i = 0; i < 13; i++) //Loop through FaceTable
		{
			if (Dealer->FaceTable[i] == 1) //Once you find a pair
			{

				for (int a = 0; a < 5; a++) //Loop through arr_of_cards
				{
					if (Dealer->arr_of_cards[a].index_face != i) //Once you find a card 
					{
						
						WhichCard = a;
						DrawOneCard(wDeck, wFace, wSuit, Dealer, CardCount, WhichCard);
					}
				}
			}

		}
	}
	else if (Dealer->HighCardValue > -1) //HIGH CARD
	{

		for (int a = 0; a < 5; a++) //Loop through arr_of_cards
		{
			if (Dealer->arr_of_cards[a].index_face != Dealer->HighCardValue) //If the card is not the high card
			{
				WhichCard = a;
				DrawOneCard(wDeck, wFace, wSuit, Dealer, CardCount, WhichCard);
			}
		}

	}

}

/******************************************************************************
*Function: DrawOneCard
*Description: Draws one card from the deck that hasn't been used and replaces it with the desired card in the hand
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer, int* CardCount, int WhichCard
*Output: void
******************************************************************************/
void DrawOneCard(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* PlayerOrDealer, int* CardCount, int WhichCard)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */


	

		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == *CardCount)
				{
					PlayerOrDealer->arr_of_cards[WhichCard].index_face = column;
					PlayerOrDealer->arr_of_cards[WhichCard].index_suit = row;


				}
			}
		}
	
	*CardCount += 1;


}

/******************************************************************************
*Function: PrintHand
*Description: Prints the hand
*Input: Hand* PlayerOrDealer, const char* wFace[], const char* wSuit[] 
*Output: void
******************************************************************************/
void PrintHand(Hand* PlayerOrDealer, const char* wFace[], const char* wSuit[])
{
	if (PlayerOrDealer->Player == 1)
	{
		printf("DEALERS HAND\n\n");
	}
	else if (PlayerOrDealer->Player == 2)
	{
		printf("YOUR HAND\n\n");
	}

	for(int i = 0; i<5; i++)
	{ 
		printf("%d. ", i);
		printf("%s of ", *(wFace + PlayerOrDealer->arr_of_cards[i].index_face));
		printf("%s\n", *(wSuit + PlayerOrDealer->arr_of_cards[i].index_suit));
	}

}

/******************************************************************************
*Function: AskToRedraw
*Description: Asks the player if they want to redraw, if yes, it redraws a desired amount of specific cards from 1-3
*Input: const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Player, int* CardCount
*Output: void
******************************************************************************/
void AskToRedraw(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* Player, int* CardCount)
{
	int choice = 0, card1 = -1, card2 = -1, card3 = -1, WhichCard = -1, valid = 0;
	do
	{
		system("cls");
		PrintHand(Player, wFace, wSuit);
		printf("\nWould you like to redraw any cards?\n1. Yes\n2. No\n3. Exit\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2 && choice != 3);

	if (choice == 1)
	{
		//Input Validation
		do
		{
			valid = 0;
			printf("\nChoose up to three cards seperated by a comma, (0, 3, 4)\n");
			int numInputs = scanf("%d,%d,%d", &card1, &card2, &card3);

			if (numInputs < 1 || numInputs > 3 || card1 < -1 || card1 > 4 || card2 < -1 || card2 > 4 || card3 < -1 || card3 > 4) {
				// Input was outside of the valid range
				system("cls");
				printf("Invalid input.\n");
				valid = 1;

				// clear input buffer
				while (getchar() != '\n');

				//Note: I understand if you enter more then 3 numbers it creates an infinite loop, I can't seem to solve this issue.
			}
		} while (valid == 1);

		//Execute Redraw
		if (card1 != -1 && card2 != -1 && card3 != -1)
		{
			WhichCard = card1;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);

			WhichCard = card2;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);

			WhichCard = card3;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);
		}
		if (card1 != -1 && card2 != -1 && card3 == -1)
		{
			WhichCard = card1;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);

			WhichCard = card2;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);


		}
		if (card1 != -1 && card2 == -1 && card3 == -1)
		{
			WhichCard = card1;
			DrawOneCard(wDeck, wFace, wSuit, Player, CardCount, WhichCard);

		}

		system("cls");
		PrintHand(Player, wFace, wSuit);
	}
	else if (choice == 3)
	{
		exit(1);
	}

}

/******************************************************************************
*Function: ComputeScore
*Description: Using the values from the combo variables in the struct to determine what the dealer or players ending score should be
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ComputeScore(Hand* PlayerOrDealer)
{
	int ComboSet = 0;

	//Create Score
	if (PlayerOrDealer->StraightFlush == 1)
	{
		PlayerOrDealer->Score = 9;
		ComboSet = 1;
	}
	if (PlayerOrDealer->FourOfAKind == 1)
	{
		PlayerOrDealer->Score = 8;
		ComboSet = 1;
	}
	if (PlayerOrDealer->FullHouse == 1)
	{
		PlayerOrDealer->Score = 7;
		ComboSet = 1;
	}
	if (PlayerOrDealer->Flush == 1)
	{
		PlayerOrDealer->Score = 6;
		ComboSet = 1;
	}
	if (PlayerOrDealer->Straight == 1)
	{
		PlayerOrDealer->Score = 5;
		ComboSet = 1;
	}

	//If you have none of the previous combos, then check for...
	if (ComboSet == 0)
	{
		if (PlayerOrDealer->ThreeOfAKind == 1)
		{
			PlayerOrDealer->Score = 4;
			
		}
		if (PlayerOrDealer->TwoPairs == 1)
		{
			PlayerOrDealer->Score = 3;
			
		}
		if (PlayerOrDealer->Pair == 1)
		{
			PlayerOrDealer->Score = 2;
		}
	}

	
}

/******************************************************************************
*Function: CompareScore
*Description: Compares the score of the Player and Dealer and outputs the result to the log file
*Input: Hand* Player, Hand* Dealer, FILE* log_file
*Output: void
******************************************************************************/
void CompareScore(Hand* Player, Hand* Dealer, FILE* log_file)
{
	int Tie = 0;
	if (Player->Score == 0 && Dealer->Score == 0)
	{
		do
		{
			Tie = 0;
			//If you have no combos compare high card
			if (Player->HighCardValue > Dealer->HighCardValue) //If none of them have aces
			{
				Player->Score = 1;
			}
			else if (Player->HighCardValue < Dealer->HighCardValue)
			{
				Dealer->Score = 1;
			}
			else if (Player->HighCardValue == Dealer->HighCardValue) //If they tie find the next highest high card 
			{
				TieHighCard(Player);
				TieHighCard(Dealer);
				Tie = 1;
			}
		} while (Tie == 1);
	}

	//Compare score and determine winner
	if (Player->Score > Dealer->Score)
	{
		printf("\nYOU WIN!\n");
		Player->Wins += 1;
		fprintf(log_file, "You won\n");

	}
	else if (Player->Score < Dealer->Score)
	{
		printf("\nYou loose\n");
		printf("\nDealer Wins\n");
		Dealer->Wins += 1;
		fprintf(log_file, "Dealer won.\n");

		
	}
	else if (Player->Score == Dealer->Score) //Note: I know it's not common to have a tie in poker, but in mine there is!
											//Note: If they tie on a high card, it will find the next highest card in their deck and use that to evaluate the winner
	{
		printf("\nITS A TIE!\n");
		fprintf(log_file, "Tie: ");


		//Display why it's a tie
		if (Player->Straight == 1)
		{
			fprintf(log_file, "Both players have a straight\n");
			printf("Both players have a straight\n");
		}
		else if (Player->Flush == 1)
		{
			fprintf(log_file, "Both players have a flush\n");
			printf("Both players have a flush\n");
		}
		else if (Player->FullHouse == 1)
		{
			fprintf(log_file, "Both players have a full house\n");
			printf("Both players have a full house\n");
		}
		else if (Player->FourOfAKind == 1)
		{
			fprintf(log_file, "Both players have a four of a kind\n");
			printf("Both players have a four of a kind\n");
		}
		else if (Player->StraightFlush == 1)
		{
			fprintf(log_file, "Both players have a straight flush\n");
			printf("Both players have a straight flush. Wow!\n");
		}
		else if (Player->Pair == 1)
		{
		fprintf(log_file, "Both players have a pair\n");
		printf("Both players have a pair\n");
		}
		else if (Player->TwoPairs == 1)
		{
		fprintf(log_file, "Both players have two pairs\n");
		printf("Both players have two pairs\n");
		}
		else if (Player->ThreeOfAKind == 1)
		{
		fprintf(log_file, "Both players have a three of a kind\n");
		printf("Both players have a three of a kind\n");
		}

	}


}

/******************************************************************************
*Function: ResetCombos
*Description: Resets all the combo variables in the struct
*Input: Hand* PlayerOrDealer
*Output: void
******************************************************************************/
void ResetCombos(Hand* PlayerOrDealer)
{
	PlayerOrDealer->HighCardValue = 0;
	PlayerOrDealer->HighCard = 0;
	PlayerOrDealer->Pair = 0;
	PlayerOrDealer->TwoPairs = 0;
	PlayerOrDealer->ThreeOfAKind = 0;
	PlayerOrDealer->Straight = 0;
	PlayerOrDealer->Flush = 0;
	PlayerOrDealer->FullHouse = 0;
	PlayerOrDealer->FourOfAKind = 0;
	PlayerOrDealer->StraightFlush = 0;
}




