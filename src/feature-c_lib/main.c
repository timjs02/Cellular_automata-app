#include <stdlib.h>
#include <stdio.h>

// Get the state of center cell in new generation based on neighborhood at t-1
int cell_state(int* old_grid, int cell_pos, int* grid_len, int* rule_table){
    //// Get neighborhood of cell, for elementary Wolfram CA == 3
    int neighborhood[3];
    // Handle edge case: first cell
    if (cell_pos == 0){
        neighborhood[0] = 0;
        neighborhood[1] = old_grid[cell_pos];
        neighborhood[2] = old_grid[cell_pos + 1];
    }
    // Handle edge case: last cell
    if (cell_pos == grid_len - 1){
        neighborhood[0] = old_grid[cell_pos - 1];
        neighborhood[1] = old_grid[cell_pos];
        neighborhood[2] = 0;
    }
    else {
        neighborhood[0] = old_grid[cell_pos - 1];
        neighborhood[1] = old_grid[cell_pos];
        neighborhood[2] = old_grid[cell_pos + 1];
    }

    //// Get new state of cell based on neighborhood
    int new_state = NULL;
    // Get value of rule table based on neighborhood: 
    // e.g. rule_table[2] represents the binary digit '1'10 in 110 (neighborhood)
    new_state = rule_table[neighborhood[2]*4 + neighborhood[1]*2 + neighborhood[0]];

    // Error handling
    if (new_state == NULL){
        printf("Error: new_state is NULL\n");
        exit(1);
    }
    return new_state;
}

// calculate the next generation of the grid
int* next_gen(int* old_grid, int* grid_len, int* rule_table){
    int new_grid[*grid_len];
    // Fill in new grid with new cell states
    for (int i = 0; i < grid_len; i++){
        // implement cell_state function
        new_grid[i] = cell_state(old_grid, i, grid_len, rule_table);
    }

    return *new_grid;
}
/*
testing:
ruleset-table: rule 90, or binary rule 01011010
                        7   6   5   4   3   2   1   0
    neihborhood ->      111 110 101 100 011 010 001 000
    center cell state-> 0   1   0   1   1   0   1   0
=> neighborhood is in reverse order in rule_table array
*/

// Handle arguments and run the program
int main(int* old_grid, int rule) {
    int grid_len = sizeof(old_grid)/sizeof(int);
    
    //// Build rule table for elementary Wolfram CA
    // Implement as array of size 8, where index represents the binary value of the neighborhood
    int rule_table[8];
    // Convert rule to binary
    int rule_bin[8];
    for (int i = 0; i < 8; i++){
        rule_bin[i] = rule % 2;
        rule = rule / 2;
    }
    // Fill in rule table with binary rule from 000 as index 0 to 111 as index 7
    for (int i = 0; i < 8; i++){
        rule_table[i] = rule_bin[7-i];
    }

    int* new_grid = next_gen(old_grid, &grid_len, &rule_table);
    return 0;
}