#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<math.h>

#define TIC_TAC_TOE_ROWS 3
#define TIC_TAC_TOE_COLUMNS 3
#define STRING_MAX_LENGTH 5

void printBoard(char array[TIC_TAC_TOE_ROWS][TIC_TAC_TOE_COLUMNS])	//printing out the gaming field in the console
{
	printf("\n"); 
	printf("| %c | %c | %c | \n",array[0][0],array[0][1],array[0][2]);
	printf("| %c | %c | %c | \n",array[1][0],array[1][1],array[1][2]);
	printf("| %c | %c | %c | \n\n\n",array[2][0],array[2][1],array[2][2]);
}

void switchPlayer(int* value) // changing the value of the integer (switching between player 1 and 2)
{
	if(*value == 1)
		*value = 2; 
	else
		*value = 1; 	
}

int chooseFromMenu() 
{
	printf("\nFor new game enter 1 \nTo replay previous games enter 2 \nFor exit enter 3 \n\n\n");
	int choice;
	do
	{
		char str[10];
		fgets(str,10,stdin);
		choice =atoi(str);
	}
	while(( choice > 3 || choice == 0) && printf("Enter valid choice \n")); 
	return choice;
}
void undoTurn(char array[TIC_TAC_TOE_ROWS][TIC_TAC_TOE_COLUMNS],int value,int* player,int* turnCounter) 
{   //removes value from last turn, prints out again the gaming field, returns the previous player
	array[value/TIC_TAC_TOE_ROWS][value%TIC_TAC_TOE_ROWS] = ' ';  
	printBoard(array); 
	switchPlayer(player);
	*turnCounter = *turnCounter-1; 
}
int addValue(char array[TIC_TAC_TOE_ROWS][TIC_TAC_TOE_COLUMNS],int value,int player) //adding a new element in the array which we use in the game field
{
	if(player == 1) 
	{
		if(array[value/TIC_TAC_TOE_ROWS][value%TIC_TAC_TOE_ROWS] == ' ') 
		{
			array[value/TIC_TAC_TOE_ROWS][value%TIC_TAC_TOE_ROWS] = 'X'; 
			return 1;
		}
		else
		{
			printf("The field is already taken \n");
			return 0;
		}
		
	}
	else if(player == 2) 
	{
		if(array[value/TIC_TAC_TOE_ROWS][value%TIC_TAC_TOE_ROWS] == ' ') 
		{
			array[value/TIC_TAC_TOE_ROWS][value%TIC_TAC_TOE_ROWS] = 'O'; 
			return 1;
		}
		else
		{
			printf("The field is already taken \n");
			return 0;
		}
		
	}
}

int checkForWinner(char array[TIC_TAC_TOE_ROWS][TIC_TAC_TOE_COLUMNS],int* winnerFlag)
{
	//checking all combinations (rows, columns and diagonals) if there's a winner
	if(((array[0][0] == array[0][1]) && (array[0][1] == array[0][2]) && array[0][0] != ' ') || ((array[1][0]) == array[1][1]) && (array[1][1] == array[1][2] && array[1][0] != ' ') 
	|| ((array[2][0] == array[2][1]) && (array[2][1] == array[2][2]) && array[2][0] != ' ') || ((array[0][0] == array[1][0]) && (array[1][0]== array[2][0]) && array[0][0] != ' ') 
	|| ((array[0][1] == array[1][1]) && (array[1][1] == array[2][1]) && array[0][1] != ' ') || ((array[0][2] == array[1][2]) && (array[1][2]== array[2][2]) && array[0][2] != ' ') 
	|| ((array[0][0] == array[1][1]) && (array[1][1] == array[2][2]) && array[0][0] != ' ') || ((array[0][2] == array[1][1]) && (array[1][1]== array[2][0])) && array[0][2] != ' ')
	{
		*winnerFlag = 1; 
		return 1;
	}	
	else 
	{
		return 0;
	}
}

void clearRedoArray(int* array,int index)
{
	int i;
	for(i = index;i < TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS;i++)
	{
		array[i] = -1; //go through the whole array and fill it with -1 because -1 can't be used (doing this to avoid the game crashing)
	}
}

void printReplays(int array[][TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS+1],int numberOfReplays) 
{
	int i = 0,j = 0,player = 1;
	printf(" %d games were played \n",numberOfReplays);
	while(i < numberOfReplays) 
	{   
		//creating an empty array which is used as a dummy array to fill in the data
		char gameForReplay[TIC_TAC_TOE_COLUMNS][TIC_TAC_TOE_ROWS] =  {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}}; 
		printf("Game %d \n",i+1);
		while(j <= (TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS)-1)
		{
			if(array[i][j] != -1)
			{

				//if the turn is valid, we add the value in the dummy array, print it out and switch players
				printf("Player %d played on field %d\n",player,array[i][j]+1); 
				addValue(gameForReplay,array[i][j],player);
				printBoard(gameForReplay);
				switchPlayer(&player);
			}
			j++;
		}
		j = 0;
		if(array[i][TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS] != -1) //the last symbol in our array with turns is the winner if there's a winner is printed out
			printf("Player %d won the game\n\n",array[i][TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS]);
		else 
			printf("Game was draw \n\n");
		i++;
	}
}

void playGame(char array[TIC_TAC_TOE_ROWS][TIC_TAC_TOE_COLUMNS],int replayArray[10][10],int numberOfReplays) //the function which controls the game
{
	int gameMovement[TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS+1];
	int i = 0;
	for(i = 0;i<=TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS;i++)
	{
		gameMovement[i] = -1; //filling it with -1 so we have validation later
	}
	int redoMoves[TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS]; 
	char string[STRING_MAX_LENGTH]; 
	int turnCounter = 0,player = 1,winnerFLag = 0;
	do
	{
		if(turnCounter >= 5) //checking for a winner after the 5th turn
		{
			if(checkForWinner(array,&winnerFLag) || (turnCounter == TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS)) 
			{
				switchPlayer(&player);
				if(winnerFLag)
				{
					printf("Player %d wins \n\n",player);
					gameMovement[TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS] = player;
				}
				else
				{
					printf("Game is draw \n");
					gameMovement[TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS] = -1; 
				}				
				printf("To return to main menu enter - m \n To undo last move - u \n\n");
				char c;
				scanf("%c", &c);
				getchar();
				if(c == 'm') 
				{
					for(i = 0;i <= TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS;i++)
					{
						replayArray[numberOfReplays-1][i] = gameMovement[i]; //saving the array with all the turns step by step so we can show it in replay
					}
					break;
				}
				else if(c == 'u')
				{
					winnerFLag = 0;
					switchPlayer(&player); 
					undoTurn(array,gameMovement[turnCounter-1],&player,&turnCounter);
				}
				else //if a wrong command is entered, we go back to main menu
				{
					for(i = 0;i <= TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS;i++)
					{
						replayArray[numberOfReplays-1][i] = gameMovement[i]; 
					}
					printf("Returning to main menu\n\n");
					break;
				}
			}
		}
		printf("Player %d your choice ? \n\n",player);
		fgets(string, STRING_MAX_LENGTH, stdin); //reading what command or number is requested by the player
		string[STRING_MAX_LENGTH-1] = '\0';
		if((string[0] == 'r'))
		{
			if(gameMovement[turnCounter] != -1) //if there are no turns, we cant give a redo
			{
				addValue(array,gameMovement[turnCounter],player);
				switchPlayer(&player); 
				turnCounter++; 
				printBoard(array); 

			}
			else
			{
				printf("There are no more moves\n");
			}
			
		}
		else if(string[0] == 'u') 
		{
			if(turnCounter != 0)
			{
				undoTurn(array,gameMovement[turnCounter-1],&player,&turnCounter); //if undo is chosen and its not the 1st turn, undo is done
			}
			else 
			{
				printf("Cant undo on first turn \n");
			}	

		}
		else if((string[2] == '\0') && ((string[0] >= '1') && (string[0] <= '9'))) 
		{
			//if the number is 1-9, it's turned in an integer because its a char and numbers in chars are 0-0x30, 1-0x31 .. 9-0x39
			int choiceNumber = string[0]-0x30; 
			if (addValue(array,choiceNumber-1,player)) 
			{
				clearRedoArray(gameMovement,turnCounter); 
				gameMovement[turnCounter] = choiceNumber-1;
				turnCounter++; 
				printBoard(array); 
			    switchPlayer(&player); 
			}
		}
		else
		{
			printf("Enter valid choice \n");
		}
		
	} while (turnCounter <= TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS); //the whole game goes until there arent 9 turns and that's the 2nd check
	
}
int main()
{ 
	int player = 0, turns = 0,isGameStarted = 0,numberOfReplays = 0;
	int replayArr[10][(TIC_TAC_TOE_COLUMNS*TIC_TAC_TOE_ROWS)+1]; //array for the replay array
	while(1)
	{
		if(isGameStarted) 
		{
			//if new game option is chosen, the game count is +1, an empty array is created, the play function is called and the flag is returned to 0
			numberOfReplays++;
			char currGame[TIC_TAC_TOE_COLUMNS][TIC_TAC_TOE_ROWS] =  {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}}; 
			playGame(currGame,replayArr,numberOfReplays);
			isGameStarted = 0;
		}
		else 
		{
			int choice = chooseFromMenu();
			if(choice == 1)
			{
				isGameStarted = 1;
			}
			else if(choice == 2)
			{		
				printReplays(replayArr,numberOfReplays);
			}
			else
			{  
				break; 
			}
		}
		
	}
	return 0;
}
