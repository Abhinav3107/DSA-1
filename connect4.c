/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
#include <stdio.h>
#include <assert.h>

#define n 4
typedef char player_t;
typedef char board_t[4][5];

void int_board(board_t board)
{
    // Horizontal Check
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            board[row][col] = '_';
        }
    }
}

int is_full(board_t board)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            if (board[row][col] == '_') // Check if vacant spot represented by _
            {
                return 0;
            }
        }
    }
    return 1;
}

int has_won(board_t board, player_t player)
{
    int count_var = 0;
    for (int i = 0; i < 4; i++)
    {
        count_var = 0;
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player)
            {
                count_var++;
            }
        }
        if (count_var == n)
        {
            return 1;
        }

        count_var = 0;
        for (int j = 1; j < 5; j++)
        {
            if (board[i][j] == player)
            {
                count_var++;
            }
        }
        if (count_var == n)
        {
            return 1;
        }
    }

    // Vertical Check
    for (int j = 0; j < 5; j++)
    {
        count_var = 0;
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j] == player)
            {
                count_var++;
            }
        }
        if (count_var == n)
        {
            return 1;
        }
    }
    count_var = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][i] == player)
        {
            count_var++;
        }
    }
    if (count_var == n)
    {
        return 1;
    }
    count_var = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][i + 1] == player)
        {
            count_var++;
        }
    }
    if (count_var == n)
    {
        return 1;
    }

    // Diagonal Checks(Top Left to Bottom Right)
    count_var = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][n - i] == player)
        {
            count_var++;
        }
    }
    if (count_var == n)
    {
        return 1;
    }

    // Main Diagonal (Top Right to Bottom Left)
    count_var = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][n - i - 1] == player)
        {
            count_var++;
        }
    }
    if (count_var == n)
    {
        return 1;
    }
    return 0; // No win detected
}

player_t another_player(player_t player)
{
    switch (player)
    {
    case 'r':
        return 'b';
    case 'b':
        return 'r';
    default:
        assert(0);
    }
}

typedef struct
{
    int col;
    int score;
} move_t;
// Filling the table
void add_element(board_t board, player_t player, int j)
{
    int p = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][j] == '_')
        {
            p = i;
        }
    }
    board[p][j] = player;
}

void remove_element(board_t board, int j)
{
    int q = 0;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][j] != '_')
        {
            q = i;
            break;
        }
    }
    board[q][j] = '_';
}
/*
 * board should be an unfinished game.
 */
move_t best_move(board_t board, player_t player)
{
    move_t reaction;
    move_t possible_move;
    int no_possible_move = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, another_player(player)));

    for (int col = 0; col < 5; ++col)
    {
        if (board[0][col] == '_')
        {
            add_element(board, player, col);
            if (has_won(board, player))
            {
                remove_element(board, col);
                return (move_t){
                    col, 1};
            }
            remove_element(board, col);
        }
    }

    for (int col = 0; col < 5; ++col)
    {

        if (board[0][col] == '_')
        {
            add_element(board, player, col);
            if (is_full(board))
            {
                remove_element(board, col);
                return (move_t){
                    col, 0};
            }

            reaction = best_move(board, another_player(player));
            remove_element(board, col);
            if (reaction.score == -1)
            {
                return (move_t){
                    .col = col,
                    .score = 1};
            }
            else if (reaction.score == 0)
            {
                possible_move = (move_t){
                    .col = col,
                    .score = 0};
                no_possible_move = 0;
            }
            else
            { /* response.score == +1 */
                if (no_possible_move)
                {
                    possible_move = (move_t){
                        .col = col,
                        .score = -1};
                    no_possible_move = 0;
                }
            }
        }
    }

    return possible_move;
}

void print_board(board_t board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n---------------------------------\n");
}

int main()
{
    board_t game;
    int_board(game);
    player_t user;
    player_t pc;
    player_t curr;
    int temp;
    int col;
    printf("Choose red or blue\n");
    printf("Enter r for Red\n");
    printf("Enter b for Blue\n");
    scanf("%s", &temp);
    if (temp == 1)
    {
        user = 'r';
        pc = 'b';
    }
    else
    {
        user = 'b';
        pc = 'r';
    }
    printf(" want to play First? \n");
    printf("If Yes, Enter 1\n");
    printf("Else, Enter 2\n");
    scanf("%d", &temp);
    if (temp == 1)
    {
        curr = user;
    }
    else
    {
        curr = pc;
    }
    if (curr == user)
    {
        printf("Your Turn (enter col 0-4): ");
        scanf("%d", &col);
        add_element(game, user, col);
        if (col == 0)
        {
            add_element(game, pc, 1);
        }
        if (col == 1)
        {
            add_element(game, pc, 4);
        }
        if (col == 2)
        {
            add_element(game, pc, 4);
        }
        if (col == 3)
        {
            add_element(game, pc, 0);
        }
        if (col == 4)
        {
            add_element(game, pc, 3);
        }
    }
    else
    {
        add_element(game, pc, 3);
        curr = user;
    }

    while (1)
    {
        print_board(game);
        if (user == curr)
        {
            printf("Your turn (enter column 0-4): ");
            scanf("%d", &col);
            if (col < 0 || col > 4 || game[0][col] != '_')
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            add_element(game, user, col);
            if (has_won(game, user))
            {
                print_board(game);
                printf("You won! celebration!\n");
                break;
            }
        }
        else
        {
            // Computer's turn
            move_t computerMove = best_move(game, curr);
            printf("Computer's turn: %d\n", computerMove.col);

            // computer move
            add_element(game, curr, computerMove.col);

            // computer has won
            if (has_won(game, curr))
            {
                print_board(game);
                printf("Computer wins!\n");
                break;
            }
        }
        curr = another_player(curr);
        if (is_full(game))
        {
            print_board(game);
            printf("Game is draw!\n");
            break;
        }
    }
    return 0;
}