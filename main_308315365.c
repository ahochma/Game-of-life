#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define EXAMPLE_LOAF {  \
    "......",           \
    "..OO..",           \
    ".O..O.",           \
    "..O.O.",           \
    "...O..",           \
    "......"}

#define EXAMPLE_BEACON {\
    "......",           \
    ".OO...",           \
    ".OO...",           \
    "...OO.",           \
    "...OO.",           \
    "......"}

#define EXAMPLE_GLIDER {\
    "......",           \
    "...O..",           \
    ".O.O..",           \
    "..OO..",           \
    "......",           \
    "......"}

// try all 3 examples! 
// e.g. change EXAMPLE_LOAF TO EXAMPLE_BEACON
// and rebulid

int main(int argc,char *argv[])
{   
    bool interactive = true;
    struct game_state gs = {.generation = N_GENERATIONS, .n_cols=MAXSIZE, .n_rows= MAXSIZE};
    if(argv[1]==NULL)
        {puts("You forgot to enter a text file name");
        exit(1);}
    else
        if(load(&gs,argv[1])==false)
            {  
                fprintf(stderr,"Something went wrong with loading your file\n");
                free_game_state(&gs);
                return(2);
                exit(0);
            }
    //printf("%d\n",atoi(argv[2]));
    //sleep(2);
    if (argv[2] != NULL)
    {
        if(atoi(argv[2])!=0)//when arg 2 is anumber
           {
            gs.generation= atoi(argv[2]);
            if(argv[3]!=NULL)
                if(strcmp("noninteractive",argv[3])==0)
                        interactive=false;}
        else{ //when arg 2 is not anumber
            if(strcmp("noninteractive",argv[2])==0)//if it string that equals to noninteractive
                {
                interactive=false;
                if(argv[3]!=NULL)
                    if(atoi(argv[3])==0)
                        gs.generation=atoi(argv[3]);
                }
            }

    }
    unsigned gen;
    for (gen = 1; gen <= gs.generation; ++gen) {
        update(&gs);
        if (interactive) {
            // display intermediate boards
            clear();
            display(&gs,gen);
            sleep(1); // one second
        }
    }
    if (!interactive) // display only final board
        display(&gs,gs.generation);

    free_game_state(&gs);
    

    return 0;
}

