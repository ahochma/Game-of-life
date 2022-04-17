#include "game.h"

/* this function is not declared in game.h since it is
   internal to game.c; it is even defined as static -- 
   so the linker won't allow using it outside of game.c */
static unsigned int count_neighbors(struct game_state *gs,unsigned i, unsigned j)

{ 
    int neighbours = 0;
    for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (!(y == 0 && x == 0)) {
                    int r = i + y;
                    int c = j + x;
                            //normalize
                if (r<0) 
                    r = gs->n_rows - 1;
                else if(r == gs->n_rows) 
                    r = 0;        
                if (c<0)
                    c = gs->n_cols - 1;
                else if (c == gs->n_cols)
                    c = 0;
                if (gs->board[r][c] == ALIVE)
                        neighbours++;
                }
        }
    }
        return neighbours;           
    return 2;
}

void update(struct game_state *gs)
{
   // unsigned n_neighbors[gs->n_rows][gs->n_cols];
    for (unsigned i = 0; i < gs->n_rows; ++i) {
        for (unsigned j = 0; j < gs->n_cols; ++j) {
           gs->n_neighbors[i][j] = count_neighbors(gs,i, j);
        }
    }

    for (unsigned i = 0; i < gs->n_rows; ++i) {
        for (unsigned j = 0; j < gs->n_cols; ++j) {
            unsigned nn = gs->n_neighbors[i][j];
            if(gs->board[i][j]==ALIVE)
               {
                    if (nn < 2 || nn >= 4)
                    gs->board[i][j] = DEAD;
               }
            else if(nn==3)
                gs->board[i][j] = ALIVE;
            // when nn == 2, the previous value is retained
        }
    }
}
 
 
