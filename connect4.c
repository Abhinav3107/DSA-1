#include <stdio.h>

#define ROWS 4
#define COLUMNS 5


/*
---- We have to design a game i.e. "connect 4" , in which two player\s
will be playing by the turn.
    The person who will connect the four points ( consequtive ), [ points can be inthe diagonla, horizontal or vertical form
    t]

then we have to decalere that player as the Winner 

for the simplicity of the results we will be declearing ( and also taking the inputs in ethe
R( first palyr) or B( second player) ) in the game. 

*/

                    // ------- Here we start the game & you enjoy while playing hte game ------ 




// Function for display on board



void display(char board[ROWS][COLUMNS])
{
    printf(" 0 1 2 3 4\n");
    printf("-----------\n");
    for (int row = 0; row < ROWS; row++)
    {
        printf("|");
        for (int col = 0; col < COLUMNS; col++)
        {
            printf("%c|", board[row][col]);
        }
        printf("\n-----------\n");
    }
    printf(" 0 1 2 3 4\n");
}





// Function to check if there's a win

int has_won(char board[ROWS][COLUMNS], char player)
{
    // Check horizontally
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col <= COLUMNS - 4; col++)
        {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
            {
                return 1;
            }
        }
    }




// Vertically checking

    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
            {
                return 1;
            }
        }
    }



int is_full(char board[ROWS][COLUMNS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            if (board[row][col] == ' ')
            {
                return 0; // The board is not full.
            }
        }
    }
    return 1; // The board is full.
}





// Check diagonally (forward slash)
    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 0; col <= COLUMNS - 4; col++)
        {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player)
            {
                return 1;
            }
        }
    }





// Check diagonally( back )

    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col <= COLUMNS - 4; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
            {
                return 1;
            }
        }
    }

    return 0;
}




// Now for the main funciton



int main()
{
    char board[ROWS][COLUMNS];
    char player = 'R';
    int turn = 1;
    int winner = 0;

    // Initialize the board
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            board[row][col] = ' ';
        }
    }

    // Play as the turns


    while (!winner && turn <= ROWS * COLUMNS)
    {
        // Displaying in the board in teh curret state
        
        display(board);

        printf("Player %c enter a play: ", player);
        int play;
        scanf("%d", &play);

        // Validate play - column range and if the column is not full
        while (play < 0 || play >= COLUMNS || board[0][play] != ' ')
        {
            printf("Invalid entry. Player %c enter a play: ", player);
            scanf("%d", &play);
        }

        // Drop checker - look for the lowest empty space
        for (int row = ROWS - 1; row >= 0; row--)
        {
            if (board[row][play] == ' ')
            {
                board[row][play] = player;
                break;
            }
        }




// Now we are checkig for the win whether we are winning or not




if (has_won(board, player))
        {
            display(board);
            if (player == 'R')
            {
                printf("Red won\n");
            }
            else
            {
                printf("Black won\n");
            }
            winner = 1;
        }

        turn++;


// We have to switch for the other payer for plaing

player = (player == 'R') ? 'B' : 'R';
    }


// We will redisplays the board


display(board);



// If someone winns than we will have to declare the win in the form of hte R or B 


if (!winner)
    {
        printf("Game over. It's a tie.\n");
    }

    return 0;
}




/* 


We had implemented the game of connect 4, with the 4 rows and 5 column 

we successfully implemented the game, and by this two players can play

turn by turn and our game will declare the winner int he form of R or B // where R for red or first player

and B for // blue or the second player


*/
