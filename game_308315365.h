#ifndef GAME_H
#include <stdbool.h>

#define MAXSIZE 10
#define N_GENERATIONS 5

#define ALIVE 'O'
#define DEAD  '.'

// this is a declaration, not a definition,
// of the global variable board
// SIZE + 1 since each row is nul-terminated

struct game_state {
    char ** board;
    unsigned **n_neighbors;
    unsigned generation;
    int n_cols;
    int n_rows;
};

void clear();
void display(struct game_state *gs,unsigned gen);
void update(struct game_state *gs);
bool load(struct game_state *gs, char const *filename);
void free_game_state(struct game_state *gs);
#endif /* GMAE_H */