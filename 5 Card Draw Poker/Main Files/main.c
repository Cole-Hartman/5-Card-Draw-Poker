#include "library.h"

int main(void)
{
	FILE* log_file = fopen("Results.log", "a");
	freopen("Results.log", "w", log_file); //Clear file every time the program starts (file saves between rounds)


	if (log_file == NULL) 
	{
		printf("Error opening log file.\n");
		return 1;
	}

	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };


	srand((unsigned)time(NULL)); /* seed random-number generator */

	int Mchoice = 0, BackToMenu = 0, CardCount = 0, EndGameOption = 0, choice2 = 0, CardChoice = 0;

	Hand Player, Dealer;
	Dealer.Player = 1;
	Player.Player = 2;

	Dealer.Wins = 0;
	Player.Wins = 0;
	//initialize frequency arrays to -1
	for (int i = 0; i < 13; i++)
	{
		Player.FaceTable[i] = -1;
	}
	for (int i = 0; i < 4; i++)
	{
		Player.SuitTable[i] = -1;
	}
	for (int i = 0; i < 13; i++)
	{
		Dealer.FaceTable[i] = -1;
	}
	for (int i = 0; i < 4; i++)
	{
		Dealer.SuitTable[i] = -1;
	}




	system("cls");


		do //Back to menu
		{
			system("cls");
			BackToMenu = 0;

			system("cls");
			do
			{
				PrintFileContents("POKER.txt");
				printf("\n\nMAIN MENU\n\n1. Play Game\n2. View Rules\n3. Exit Game\n");
				scanf("%d", &Mchoice);
			} while (Mchoice != 1 && Mchoice != 2 && Mchoice != 3);

			switch (Mchoice)
			{
			case 1: //Play Game


				do //Play again
				{
					system("cls");
					EndGameOption = 0;

					Player.Score = 0;
					Dealer.Score = 0;

					ResetCombos(&Player);
					ResetCombos(&Dealer);

					/* initalize deck array */
					int deck[4][13] = { 0 };

					shuffle(deck);
					CardCount = 0;

					system("cls");
					printf("\nDealer is drawing their hand");
					PrintFileContents("DRAWING.txt");
					printf("\n");
					system("pause");
					deal(deck, face, suit, &Dealer);


					printf("\nTo recieve your cards ");
					system("pause");
					system("cls");
					printf("\nDealer is drawing your hand");
					PrintFileContents("DRAWING.txt");
					printf("\n");
					system("pause");
					deal(deck, face, suit, &Player);
					system("pause");

					CardCount = 10;

					//Create frequency arrays for Dealer and Player
					FaceFrequencyTable(&Player);
					SuitFrequencyTable(&Player);
					FaceFrequencyTable(&Dealer);
					SuitFrequencyTable(&Dealer);

					system("cls");
					printf("\nDealer is redrawing their hand");
					PrintFileContents("DRAWING.txt");
					printf("\n");

					system("pause");
					system("cls");
					AIRedraw(deck, face, suit, &Dealer, &CardCount);
					
					//Make new Frequency tables after dealer redraw
					FaceFrequencyTable(&Dealer);
					SuitFrequencyTable(&Dealer);

					//After dealer redraws, reset combos and then find combos for new hand
					ResetCombos(&Dealer); 

					OneOrTwoPairs(&Dealer);
					ThreeOrFourOfAKind(&Dealer);
					FullHouse(&Dealer);
					Flush(&Dealer);
					Straight(&Dealer);
					StraightFlush(&Dealer);
					HighCard(&Dealer);


					AskToRedraw(deck, face, suit, &Player, &CardCount);
					
					//Make new Frequency tables after redraw
					FaceFrequencyTable(&Player);
					SuitFrequencyTable(&Player);

					//After Player redraws, reset combos and then find combos for new hand
					ResetCombos(&Player);

					OneOrTwoPairs(&Player);
					ThreeOrFourOfAKind(&Player);
					FullHouse(&Player);
					Flush(&Player);
					Straight(&Player);
					StraightFlush(&Player);
					HighCard(&Player);

					CardChoice = 0;
					do
					{
						
						printf("\nAre you ready to put your cards down?\n1. Yes\n2. Exit\n");
						scanf("%d", &CardChoice);

					} while (CardChoice != 1 && CardChoice != 2);

					if (CardChoice == 1)
					{
						system("cls");
						PrintHand(&Player, face, suit);
						printf("\n");
						PrintHand(&Dealer, face, suit);

						ComputeScore(&Dealer);
						ComputeScore(&Player);
						CompareScore(&Player, &Dealer, log_file);
						system("pause");
					}
					else if (CardChoice == 2)
					{
						fclose(log_file);
						exit(1);
					}

					int PlayAgain = 0;
					printf("\n1. Play Again\n2. Return To Menu\n3. Exit\n");
					scanf("%d", &EndGameOption);


				} while (EndGameOption == 1);

				break;
			case 2: //View Rules
				do
				{
					choice2 = 0;
					system("cls");
					print_rules();
					printf("\n\n\n1. Back\n2. Exit\n");
					scanf("%d", &choice2);
				} while (choice2 != 1 && choice2 != 2);


				if (choice2 == 1)
				{
					BackToMenu = 1;
				}
				else if (choice2 == 2)
				{
					fclose(log_file);
					exit(1);
				}
				break;

				
			case 3: //Exit
				fclose(log_file);
				exit(1);
				break;

			}
		

			if (EndGameOption == 2)
			{
				BackToMenu = 1;
			}
			else if (EndGameOption == 3)
			{
				fclose(log_file);
				exit(1);

			}

		
		}while (BackToMenu == 1);

	return 0;
}
