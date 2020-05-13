/* 
Program Name: BattleshipGame.c 
Programmer: Taylor Tate
*/ 

//the header files used in the program
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

//protyping the functions used in the program
void setBoard(char *ptr);
void setComputerBoard(char *ptr);
int playGame(char *humanPrt, char *cpuPrt);

//declaring arrays to keep track of game board and varibles used in main
char humanBoard[10], cpuBoard[10];
int winner, k;


int main(void) {

  //setting pointers to the arrays that keep up with the game boards
  char *prtHuman = humanBoard;
  char *ptrCpu = cpuBoard;

  //Seeding srand so that the rand function will provide random ints
  srand(time(0)); 

  //populating the array game boards with asterisks
  for(k =0; k <10; k++)
  {
    prtHuman[k] = '*';
    ptrCpu[k] = '*';
  }

  //greeting to begin the game
  printf("Welcome to the game of Battleship.\n");
  printf("Please setup your gameboard.\n");

  //function call that sets up the human's game board
  setBoard(prtHuman);
  
  //function call that sets up the computer's game board
  setComputerBoard(ptrCpu);
  
  //function call to start the game and also sets the winner variable to the value that playGame returns
  winner = playGame(prtHuman, ptrCpu);
  
  //else if statement to determine who wins the game after the playGame function returns int value
  if (winner == 0)
  {
    printf("Computer wins!\n");
  }
  else if (winner == 1)
  {
    printf("Human wins!\n");
  }
  else if (winner == 2)
  {
    printf("An error has occured\n");
  }

  return 0;
}

void setBoard(char *ptr)
{
  //declaring varibles to be used in the function
  int firstPosition, secondPosition, flag = 0;
  
  printf("Pick two consectutive spots on your board to place a ship.\n");

  //while loop to keep getting input for user if they eneter the ship positions
  while(flag == 0) 
  {
    //Statments to get the position of the users ship 
    printf("Enter 1st position: ");
    scanf("%d", &firstPosition);
    printf("Enter 2nd position: ");
    scanf("%d", &secondPosition);

    //if else statment to make sure the user does not enter ship positions that are not consectutive or are greater than 9
    if ((secondPosition == (1 + firstPosition)) || (firstPosition == (1 + secondPosition)) & (firstPosition < 10 & secondPosition < 10 ))
    {
      //sets the ship positions on the game board
      ptr[firstPosition] = 'S';
      ptr[secondPosition] = 'S';
      //sets flag to one to release the program from the while loop
      flag = 1;
    }
    else if (firstPosition > 9 || secondPosition > 9)
    {
      printf("Please enter a number between 1 and 9.\n");
    }
    else
    {
      printf("Please enter two consecutive spots on your playing board.\n");
    }
  }
}

void setComputerBoard(char *ptr)
{
  //declaring varibles to be used in the function
  int firstPosition, secondPosition, flag = 0;

  //while loop that keeps going until the computer has generated two random ship positions that are consectutive
  while(flag == 0)
  {
    //generates computers random ship positions
    firstPosition = (rand() % 10);
    secondPosition =  (rand() % 10);

    //if statement to make sure the computer has generated two consecutive ship positions
    if (secondPosition == (1 + firstPosition) || firstPosition == (1 + secondPosition))
    {
      //sets the ship positions on the game board
      ptr[firstPosition] = 'S';
      ptr[secondPosition] = 'S';
      //sets flag to one to release the program from the while loop
      flag = 1;
    }
  }
}

int playGame(char *humanPrt, char *cpuPrt)
{
  //declaring varibles to be used in the function
  int cpuGuess, humanGuess, i, t, j, cpuFlag = 0, humanFlag = 0, gameFlag = 0;

  //while loop that keeps going until either the computer wins or the human wins
  while (gameFlag == 0)
  {

    //while loop that keeps going until the computer enters position it has not tried before
    while(cpuFlag == 0)
    {
      //generates random guess for the computer
      cpuGuess = (rand() % 10);
      
      //for loop to iterate over the game board array
      for(i = 0; i < 10; i++)
        {
          //if statement to check if that guess has already been made
          if ((humanBoard[cpuGuess] == 'M' || humanBoard[cpuGuess] == 'H'))
          {
            //sets flag to 0 so that way the computer can genrate a guess it has not made
            cpuFlag = 0;
          }
          else
          {
            //sets flag to one to release the program from the while loop
            cpuFlag = 1;  
          }  
        }
    }
    
    //print statement to show what the computer has guessed
    printf("Computer guesses %d\n", cpuGuess);
    
    //if else statement to determine if the computer's guess is a hit or a miss
    if(humanPrt[cpuGuess] == 'S')
    {
      //prints hit and marks the hit in the game board array of the human
      printf("HIT!\n");
      humanPrt[cpuGuess] = 'H';
    }
    else
    {
      //prints miss and marks the miss in the game board array of the human
      printf("MISS!\n");
      humanPrt[cpuGuess] = 'M';
    }

    //for loop and print statments to print out the new game boards for both players
    printf("Human Board:\n");
    for(i = 0; i < 10; i++)
    {
      printf("%d", i);
    }
    printf("\n");
    for(i = 0; i < 10; i++)
    {
      printf("%c", humanBoard[i]);
    }
    printf("\n");
    printf("Computer Board:\n");
    for(i = 0; i < 10; i++)
    {
      printf("%d", i);
    }
    printf("\n");
    for(i = 0; i < 10; i++)
    {
      if(cpuBoard[i] == 'S'){
      	printf("%c", '*');
	  } else {
	  	printf("%c", cpuBoard[i]);
	  }
    }
    printf("\n");

    //for loop to iterate through the game boards
    for (i = 0; i < 10; i ++)
    {
      t = i - 1;
      j = i + 1;
      
      //if else statement to figure out if anyone has won the game yet
      if (humanPrt[i] == 'H' & humanPrt[t] == 'H')
      {
        return 0;
      }
      else if (humanPrt[i] == 'H' & humanPrt[j] == 'H')
      {
        return 0;
      }
      else if(cpuPrt[i] == 'H' & cpuPrt[t] == 'H')
      {
        return 1;
      }
      else if(cpuPrt[i] == 'H' & cpuPrt[j] == 'H')
      {
        return 1;
      }
    }

    //while loop that keeps looping until the human enters a valid guess they have not made yet
    while(humanFlag == 0)
    {
      //statement to get guess from human
      printf("Enter guess: ");
      scanf("%d", &humanGuess);

      //for loop to iterate through the game boards
      for(i = 0; i < 10; i++)
        {
          //if else statement to make sure the human's guess is valid and has not been entered yet 
          if ((cpuBoard[humanGuess] == 'M' || cpuBoard[humanGuess] == 'H'))
          {
            humanFlag = 0;
            if(i == 9)
            {
               printf("You have already guessed this location please enter another guess.\n");
            }
          }
          else if (humanGuess > 10)
          {
            if(i == 9)
            {
               printf("You have entered an invalid number please enter another guess between 0 and 9.\n");
            }
          }
          else
          {
            humanFlag = 1;  
          }  
        }
    }
    
    //print statement to show what the human guessed
    printf("You guessed %d\n", humanGuess);

    //if else statement to determine if the human's guess is a hit or a miss
    if(cpuPrt[humanGuess] == 'S')
    {
      //prints hit and marks on the computer's board where the hit is
      printf("HIT!\n");
      cpuPrt[humanGuess] = 'H';
    }
    else
    {
      //prints miss and marks on the computer's board where the miss is
      printf("MISS!\n");
      cpuPrt[humanGuess] = 'M';
    }

    //for loop and print statments to print out the new game boards for both players
    printf("Human Board:\n");
    for(i = 0; i < 10; i++)
    {
      printf("%d", i);
    }
    printf("\n");
    for(i = 0; i < 10; i++)
    {
      printf("%c", humanBoard[i]);
    }
    printf("\n");
    
    printf("Computer Board:\n");
    for(i = 0; i < 10; i++)
    {
      printf("%d", i);
    }
      printf("\n");
    for(i = 0; i < 10; i++)
    {
      if(cpuBoard[i] == 'S'){
      	printf("%c", '*');
	  } else {
	  	printf("%c",  cpuBoard[i]);
	  }
    }
      printf("\n");
    //for loop to iterate through the game boards
    for (i = 0; i < 10; i ++)
    {
      t = i - 1;
      j = i + 1;
      //if else statement to figure out if anyone has won the game yet
      if (humanPrt[i] == 'H' & humanPrt[t] == 'H')
      {
        return 0;
      }
      else if (humanPrt[i] == 'H' & humanPrt[j] == 'H')
      {
        return 0;
      }
      else if(cpuPrt[i] == 'H' & cpuPrt[t] == 'H')
      {
        return 1;
      }
      else if(cpuPrt[i] == 'H' & cpuPrt[j] == 'H')
      {
        return 1;
      }
    }
    //sets the flags for the guess while loops back to zero so the whole while loop does not loop infinitly using the same guesses
    humanFlag = 0;
    cpuFlag = 0;

  }

  return 2;
}
