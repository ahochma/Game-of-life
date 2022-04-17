#include "game.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// clear terminal screen
void clear()
{
    printf("\e[2J\e[H"); // magic!
}

// display board and current generation
void display(struct game_state *gs,unsigned gen)
{
    printf("Game generation %u\n", gen);
    for (unsigned i = 0; i < gs->n_rows; ++i) {
        puts(gs->board[i]);
    }
    fflush(stdout); // make sure it gets displayed
}

// returns true if load was successful
//original func
// bool load(struct game_state *gs, char const *filename)
// {
//     assert(gs && filename);
//     return false;
// }


void free_game_state(struct game_state *gs)
 {
    char**ptr=gs->board;
    for (int i = 0; i < gs->n_rows; i++)
    {
        char* currentIntPtr = ptr[i];
        free(currentIntPtr);
        
    }
    free(ptr);
    unsigned**ptr2=gs->n_neighbors;
    for (int j = 0; j < gs->n_rows+1; j++)
    {
        unsigned* currentIntPtr2 = ptr2[j];
        free(currentIntPtr2);
        
    }
    free(ptr2);
    
 }
bool load(struct game_state *gs, char const *filename)
{   int rows; int cols;
    int ch;    
    FILE *fPtr  = fopen(filename, "r");
    assert(gs && filename);
    fscanf(fPtr,"%d",&rows);
    fgetc(fPtr);
    fscanf(fPtr,"%d",&cols);
    //allocating matrix of neighbors
    unsigned **n_mat = (unsigned **)malloc(rows * sizeof(unsigned*));
    for(int i = 0; i < rows; i++) n_mat[i] = (unsigned *)malloc(cols * sizeof(unsigned));
    gs->n_neighbors=n_mat;

    //allocating matrix of board
    char **mat = (char **)malloc(rows * sizeof(char*));
    for(int i = 0; i < rows; i++) mat[i] = (char *)malloc(cols * sizeof(char));
    gs->board=mat;

    if(mat == NULL||n_mat ==NULL)//check if malloc failed
    {
        free_game_state(gs);
        printf("Memory allocation failed");
        return false;
    }

    if(rows>MAXSIZE||cols>MAXSIZE)
        {
            printf("Unsupported size\n");
            fclose(fPtr);
            return false;
        }
    gs->n_cols=cols;gs->n_rows=rows;
    fgetc(fPtr);//to pass the \n char and to be with the pointer on the start of the matrix
    //start of matrix
    size_t i = 0, j = 0;
    while (true)
     {
        ch = fgetc(fPtr);
        if (ch == EOF) break;
        if (ch == '\n') 
        {
            ++i;
            
            if (j!=cols){fclose(fPtr); return false;}
            j=0;
            continue;
        }
        else
        {   
            if(ch==ALIVE||ch==DEAD)       
                gs->board[i][j]=ch;
            else {fclose(fPtr); return false;}
            ++j;
        }
    }
   
    if(i!=rows) {fclose(fPtr); return false;}
    fclose(fPtr);
    return true;
}
