#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


void NewGame();
void displayGameStatus(int scores[], int round, int players);
void loadGame();
void shuffleDeck();
void gameSelectionOptions();

FILE* filep;

char gameName[40];
char loadGameName[40];
char gameNameAll[40];

int player[10][13] = { 0 };
int cards[4][13] = { { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
				{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
				{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
				{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 } };
int playerScore[10];
int numberOfPlayers;
int currentRoundNumber;
int i, j, k;
int num_char;
int ifNewGame = 0;
int loadSelection;
int exitSelection;


void main()
{

	int intitialGameSelection;
	int chosenCards[10];
	int roundCounter = 0;
	int cardSelection;
	int largestCard = 0;
	int largestPlayerNumber;
	int largestOverallScore = 0;
	int winningPlayer;
	int currentRoundScore = 0;
	int nextRoundChecker;
	int nextRoundScore = 0;
	int oldValue = 0;

	printf("Please Choose an Option: \n(1) New Game\n(2) Load\n(0) Exit\n");
	scanf("%d", &intitialGameSelection);

	// while loop to initialize game
	while (intitialGameSelection != 0)
	{
		if (intitialGameSelection == 1)
		{
			NewGame();
		}

		else if (intitialGameSelection == 2)
		{
			loadGame();
		}

		else
		{
			printf("The value entered is invalid, please try again.\n");
		}


		if (intitialGameSelection == 1 || intitialGameSelection == 2)
		{
			for (i = currentRoundNumber; i < 13; ++i)
			{
				roundCounter++;
				printf("\nWelcome to Your Game of War");
				printf("\n=========ROUND %d==========\n", i + 1);

				for (j = 0; j < 10; j++)
				{
					chosenCards[j] = 0;
				}

				for (j = 0; j < numberOfPlayers; j++)
				{

					printf("\nPlayer %d: Your cards =========================\n", j + 1);

					for (k = 1; k < 14; k++)
					{
						printf("%d  ", player[j][k]);
					}
					printf("\n");
					printf("==============================================\n\n");


					do
					{
						printf("Which Card Would You Like To Play In Round %d\n", i + 1);
						printf("Numbers from 1 - 13, e.g the first card = 1 / the third card = 3 etc.\n");
						scanf("%d", &cardSelection);

					} while (cardSelection < 0 || cardSelection > 14  ); //player[j][cardSelection] == 0);

					
					chosenCards[j] = player[j][cardSelection];

					player[j][cardSelection] = 0;

					system("@cls||clear");
				}

				printf("\n");

				
				printf("Round %d Selections and Scores ============\n", i + 1);


				//Printing out round number and current scores
				for (j = 0; j < numberOfPlayers; j++)
				{
					printf("Player %d: ", j + 1);
					printf("%d \n", chosenCards[j]);

					currentRoundScore += chosenCards[j];
				}

				for (j = 0; j < numberOfPlayers; j++)
				{
					oldValue = chosenCards[j];

					for (k = 0; k < numberOfPlayers; k++)
					{
						if (k == j)
						{
							continue;
						}

						if (oldValue == chosenCards[k])
						{
							chosenCards[j] = 0;
							chosenCards[k] = 0;
						}
					}
				}

				nextRoundChecker = 0;

				for (j = 0; j < numberOfPlayers; j++)
				{
					if (chosenCards[j] >= largestCard)
					{
						largestCard = chosenCards[j];
						largestPlayerNumber = j + 1;
					}


					if (chosenCards[j] > 0)
					{
						nextRoundChecker = 1;
					}
				}


				if (nextRoundChecker == 0)
				{
					nextRoundScore = currentRoundScore;
					printf("\nThe Round is a Draw, %d Points Will be Carried Over to the Next Round\n", nextRoundScore);
				}
				else
				{

					if (nextRoundScore > 0)
					{
						currentRoundScore += nextRoundScore;
					}


					playerScore[largestPlayerNumber - 1] += currentRoundScore;

					printf("\nThe Winner of Round %d is Player %d\n", i + 1, largestPlayerNumber);
					printf("Player %d's Score is Now: %d\n", largestPlayerNumber, playerScore[largestPlayerNumber - 1]);
					
				}
				

				if (i < 12)
				{
					gameSelectionOptions();
				}

				currentRoundScore = 0;

			}

			displayGameStatus(playerScore, i, numberOfPlayers);

			// for loop to find winner
			for (i = 0; i < numberOfPlayers; i++)
			{
				if (playerScore[i] > largestOverallScore)
				{
					largestOverallScore = playerScore[i];
					winningPlayer = i + 1;
				}
			}

			printf("\nThe Winner of the War is Player %d with a Total Score of: %d\n", winningPlayer, largestOverallScore);

			printf("\n\nThe War has Ended, Go in Peace !!!\n\n\n");

		}


		printf("Please Choose an Option: \n(1) New Game\n(2) Load\n(0) Exit\n");
		scanf("%d", &intitialGameSelection);
	}
}





void NewGame()
{
	int suit = 0;
	int randomCardPos;

	printf("Please Enter a Name for Your New Game: \n");
	scanf("%s", gameName);

	strcat(gameName, ".txt");

	do
	{
		printf("Please Choose Number of Players (2 - 10): \n");
		scanf("%d", &numberOfPlayers);
	} while (numberOfPlayers < 2 || numberOfPlayers > 10);


	for (i = 0; i < numberOfPlayers; i++)
	{
		playerScore[i] = 0;
	}


	currentRoundNumber = 0;
	ifNewGame = 1;



	srand(time(NULL));

	for (i = 0; i < numberOfPlayers; i++)
	{
		shuffleDeck();

		for (j = 0; j < 13; j++)
		{
			randomCardPos = rand() % 13;
			player[i][j] = cards[suit][randomCardPos];

			suit++;
			if (suit == 3)
			{
				suit = 0;
			}
		}
	}
}



void shuffleDeck()
{
	int randomNum;
	int oldCardValue;
	int i;


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 13; j++)
		{
			randomNum = rand() % 13;
			oldCardValue = cards[i][randomNum];
			cards[i][randomNum] = cards[i][j];
			cards[i][j] = oldCardValue;
		}
	}
}



void loadGame()
{
	printf("Game Selection =====================\n");


	filep = fopen("allGameNames.txt", "r");

	if (filep == NULL)
	{
		printf("This File Cannot be Opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			num_char = fscanf(filep, "%s", gameNameAll);
			if (num_char > 0)
			{
				printf("%s\n", gameNameAll);
			}
		}
		printf("\n");

	}
	fclose(filep);


	printf("Please Enter the Name of the Game you Would Like to Load: \n");
	scanf("%s", loadGameName);


	strcpy(gameName, loadGameName);

	filep = fopen(loadGameName, "r");

	if (filep == NULL)
	{
		printf("This File Cannot be Opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			fscanf(filep, "%d", &numberOfPlayers);
			fscanf(filep, "%d", &currentRoundNumber);


			for (i = 0; i < numberOfPlayers; i++)
			{
				for (j = 0; j < 13; j++)
				{
					fscanf(filep, "%d", &player[i][j]);
				}
			}


			for (i = 0; i < numberOfPlayers; i++)
			{
				fscanf(filep, "%d ", &playerScore[i]);
			}

			printf("\nGame %s is Loaded\n", gameName);
		}
		fclose(filep);

		displayGameStatus(playerScore, i, numberOfPlayers);
	}
}



void displayGameStatus(int scores[], int round, int players)
{
	int i;

	printf("\nRound: %d\n", round + 1);
	printf("Number of Players: %d\n\n", players);

	printf("===== Scores =====\n");

	for (i = 0; i < players; i++)
	{
		printf("Player %d: %d\n", i + 1, scores[i]);
	}
}



void gameSelectionOptions()
{
	printf("\n1 - Go to Next Round\n2 - Save your Game\n3 - View Game Scores\n4 - Exit Game Without Saving\n");
	scanf("%d", &loadSelection);

	switch (loadSelection)
	{
	case 1:

		break;
	case 2:

		filep = fopen(gameName, "w");

		if (filep == NULL)
		{
			printf("The file could not be opened\n");
		}

		else
		{
			fprintf(filep, "%d\n", numberOfPlayers);
			fprintf(filep, "%d\n", i);

			for (j = 0; j < numberOfPlayers; j++)
			{
				for (k = 0; k < 13; k++)
				{
					fprintf(filep, "%d ", player[j][k]);
				}
				fprintf(filep, "\n");
			}

			for (j = 0; j < numberOfPlayers; j++)
			{
				fprintf(filep, "%d ", playerScore[j]);
			}

			fclose(filep);
		}



		if (ifNewGame == 1)
		{

			filep = fopen("allGameNames.txt", "a");

			if (filep == NULL)
			{
				printf("The file could not be opened\n");
			}

			else
			{
				fprintf(filep, "%s\n", gameName);
				fclose(filep);
			}
		}
		break;
	case 3:
		displayGameStatus(playerScore, i, numberOfPlayers);
		break;
	case 4:

		printf("\n1 - Open a new Game\n2 - Open a Previously Saved Game\n3 - Exit Application\n");
		scanf("%d", &exitSelection);

		if (exitSelection == 1) {
			NewGame();
			i = -1;
		}
		else if (exitSelection == 2)
		{
			loadGame();
			i = currentRoundNumber - 1;
		}
		else if (exitSelection == 3) {

			exit(0);
		}
		else {
			printf("Value Entered is Invald");
		}
		break;
	default:
		printf("Value Entered is Invald");
		break;
	}
}
