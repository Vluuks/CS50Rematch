/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // HIER NIET NOG EEN KEER BOARD DELCAREREN, ANDERS DAN SNAPT DRAW HEM NIET
    // UREN MEE BEZIG GEWEEST WIST IK VEEL DAT ER BOVENAAN OOK AL BOARD STOND >:C NIET GOED OPGELET
    // determine maximal number to be inserted into array
    int maxnum = (d*d) - 1;
    
    //loop over every row
    for(int i = 0; i < d; i++){
        
        // and every column inside this row
        for(int j = 0; j < d; j++){
            
            // insert number at place in array row i colum j, decreasing the value to be inserted every round
            board[i][j] = maxnum;
            maxnum = maxnum - 1;
            }
    }
    
    // if the number of tiles in the game is odd then swap 1 and 2
    // they mean the tiles used not the actual amount of tiles on the board which is a bit confusing
    if ( ((d*d)-1)%2 != 0)
    {
        // the array is zero indexed so d-1 is actually the last row, not d
        // also so d-3 is the second last of the tiles and holds 2, because the very last spot is taken by 0 which is not part of the game
        
        // store number 1 in a temporary int
        // could also be assigned 1 directly which is perhaps more straightforward for some people
        int toswap = board[d-1][d-2];
        
        // make the spot in the array of 1 hold the value of [d-3], in this case 2
        board[d-1][d-2] = board[d-1][d-3];
        
        // make the spot in the array of 2 hold the temporary value, 1
        board[d-1][d-3] = toswap;
    }      
    
}
    
    

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // prints every row
    for( int i = 0; i < d; i++){
        
        // prints every column
        for ( int j = 0; j < d; j++){
            
            if(board[i][j] == 0)
                printf("[  ]");
            else if(board[i][j] < 10)
                printf("[ %i]", board[i][j]);
            else if(board[i][j] > 9)
                printf("[%i]", board[i][j]);
        }
        
        //newline
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool canmove = false;
    int tilerow;
    int tilecolumn;
    int blanktilerow;
    int blanktilecolumn;
    
    // search for the position of the tile in the array first
    for( int i = 0; i < d; i++){
        
        for ( int j = 0; j < d; j++){
            
            // if the tile in question is found:
            if (board[i][j] == tile)
            {
                // get the number of the row that the tile is on
                // 0 is first row, d-1 is last row
                tilerow = i;
                tilecolumn = j;
                blanktilerow = -1;
                blanktilecolumn = -1;
                
                // check above the tile
                // if its not the upper row and the row above contains the 0 tile at the same y location, then there can be a move
                if (tilerow > 0 && board[tilerow - 1][tilecolumn] == 0){
                    canmove = true;
                    blanktilerow = tilerow - 1;
                    blanktilecolumn = tilecolumn;
                }
                // check under the tile
                // if it's not the last row (which would be d-1) and the row below contains the 0 tile at the same y location, then there can be a move
                else if (tilerow <= d-2 && board[tilerow + 1][tilecolumn] == 0){
                    canmove = true;
                    blanktilerow = tilerow + 1;
                    blanktilecolumn = tilecolumn;
                }
                // check left of the tile
                // if it's not the first column and the column left of it contains the 0 tile at the same x location, then there can be a move
                else if (tilecolumn > 0 && board[tilerow][tilecolumn - 1] == 0){
                      canmove = true;
                    blanktilerow = tilerow;
                    blanktilecolumn = tilecolumn - 1;
                }
                // check right of the tile
                // if it's not the last column and the column right of it contains the 0 tile at the same x location, then there can be a move
                else if (tilecolumn <= d-2 && board[tilerow][tilecolumn + 1] == 0){
                    canmove = true;
                    blanktilerow = tilerow;
                    blanktilecolumn = tilecolumn + 1;
                }
                // if none of this is the case, then there can be no move
                else
                    canmove = false;
            }
        }
    }
    
    
    // if there can be a move, swap tiles and return true
    if(canmove != false){
        
        // create temporary values to move things around
        int temp_value = board[tilerow][tilecolumn];

        // replace the value with the blank value
        board[tilerow][tilecolumn] = 0;
        board[blanktilerow][blanktilecolumn] = temp_value;
        return true;
    }
        
    // else return false
    else
        return false;

}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 1;
    
    // loop over the board, per row and column
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            
            // if the position of the tile on the board matches the counter, increment counter and then check again
            // to see if everything is in the correct order
            if (board[i][j] == counter){
                counter++;
                
                // if the counter reached the dimensions , not d*d-1 because ther is 1 more ++ after the last numbered tile which brings it to d*d value
                if (counter == d*d && board[d-1][d-1] == 0) 
                    return true;
            }
        } 
    }
    return false;
}