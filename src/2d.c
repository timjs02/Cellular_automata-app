#include <stdlib.h>
#include <stdio.h>

/*
Create 2D Cellular Automata: Conway's Game of Life
Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

https://www.ibiblio.org/lifepatterns/october1970.html
"
Survivals. Every counter with two or three neighboring counters survives for the next generation.
Deaths. Each counter with four or more neighbors dies (is removed) from overpopulation. Every counter with one neighbor or none dies from isolation.
Births. Each empty cell adjacent to exactly three neighbors--no more, no fewer--is a birth cell. A counter is placed on it at the next move.
"
Conway recommends the following procedure for making the moves:

Start with a pattern consisting of black counters.
Locate all counters that will die. Identify them by putting a black counter on top of each.
Locate all vacant cells where births will occur. Put a white counter on each birth cell.
After the pattern has been checked and double-checked to make sure no mistakes have been made, remove all the dead counters (piles of two) and replace all newborn white organisms with black counters.

*/
// Von Neumann Neighbourhood: 4, Moore Neighbourhood: 8
# define NBH_SIZE 8
# define ROWS 10
# define COLS 10
# define GEN_COUNT 10

// Get neighbors
void get_neighbors(int* grid[COLS][ROWS], int x, int y, int* neighbors[NBH_SIZE]){
    if (NBH_SIZE >= 4){
        // Find neighbors in Von Neumann Neighbourhood
        if (y-1 < 0 || y+1 >= ROWS){
            if (y-1 < 0){
                neighbors[0] = grid[x][ROWS-1];
            }
            else if (y+1 >= ROWS){
                neighbors[1] = grid[x][0];
            }
        }
        else if (x-1 < 0 || x+1 >= COLS){
            if (x-1 < 0){
                neighbors[2] = grid[COLS-1][y];
            }
            else if (x+1 >= COLS)
            {
                neighbors[3] = grid[0][y];
            }
        }
        else {
            for (int i = 0; i < NBH_SIZE; i++){
                neighbors[i] = 0;
            }
            neighbors[0] = grid[x][y-1];
            neighbors[1] = grid[x][y+1];
            neighbors[2] = grid[x-1][y];
            neighbors[3] = grid[x+1][y];
        }
        // Find neighbors in Moore Neighbourhood
        if (NBH_SIZE == 8){
            if (x-1<0){
                if (y-1<0){
                    neighbors[4] = grid[COLS-1][ROWS-1];
                }
                else if (y+1>=ROWS){
                    neighbors[5] = grid[COLS-1][0];
                }
                else {
                    neighbors[4] = grid[COLS-1][y-1];
                    neighbors[5] = grid[COLS-1][y+1];
                }
            }
            else if (x+1>=COLS){
                if (y-1<0){
                    neighbors[6] = grid[0][ROWS-1];
                }
                else if (y+1>=ROWS){
                    neighbors[7] = grid[0][0];
                }
                else {
                    neighbors[6] = grid[0][y-1];
                    neighbors[7] = grid[0][y+1];
                }
            }
            else {
                
            }
        }
    }
}

// Get the number of live neighbors
int get_live(int* grid[COLS][ROWS], int x, int y){
    int live_neighbors = 0;
    int neighbors[NBH_SIZE];
    get_neighbors(grid, x, y, neighbors);
    for (int i = 0; i < NBH_SIZE; i++){
        if (neighbors[i] == 1){
            live_neighbors++;
        }
    }
    
    return live_neighbors;
}

// Calculate the next state of the grid
void next_grid_calc(int* grid[COLS][ROWS], int* next_grid[COLS][ROWS]){
    for (int x = 0; x < COLS; x++){
        for (int y = 0; y < ROWS; y++){
            // Get the state of the cell
            int state = grid[x][y];

            // Locate all cells that will die
            int live_neighbors = get_live(grid, x, y);
            
            /// Apply the rules
            
            // Death
            if (live_neighbors < 2){
                next_grid[x][y] = 0;
            }
            else if (live_neighbors > 3){
                next_grid[x][y] = 0;
            }

            // Birth
            else if (state == 0 && live_neighbors == 3){
                next_grid[x][y] = 1;
            }
            // Survival (redundant?)
            else if (live_neighbors == 2 || live_neighbors == 3){
                next_grid[x][y] = 1;
            }
            
        }
    }
}

// Initial conditions
void initial_conditions(int *grid[COLS][ROWS]){
    for (int x = 0; x < COLS; x++){
        for (int y = 0; y < ROWS; y++){
            grid[x][y] = 0;
        }
    }
    
    // Top Left Corner = 1
    grid[0][0] = 1;
}

// Run a generation
void gen(int *grid[COLS][ROWS], int *next_grid[COLS][ROWS]){
    
    // Calculate the next state of the grid
    next_grid_calc(grid, next_grid);

    // Update the grid
    for (int x = 0; x < COLS; x++) {
        for (int y = 0; y < ROWS; y++) {
            grid[x][y] = next_grid[x][y];
        }
    }

    // Print the grid
    for (int x = 0; x < COLS; x++) {
        for (int y = 0; y < ROWS; y++) {
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
}

int main(){
    // Handle initial conditions
    int grid[COLS][ROWS];
    int next_grid[COLS][ROWS];
    initial_conditions(grid);

    for (int i = 0; i < GEN_COUNT; i++) {
        gen(grid, next_grid);
    }
    return 0;
}