#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

/// @param grid Pointer to the grid
/// @param size Size of the grid (assuming square grid)
/// @param x x coordinate
/// @param y y coordinate
/// @return Number of alive neighbors
int neighborhood_M(int** grid, int size, int x, int y) {
    int sum = 0;
    
    // Iterate through the Moore neighborhood (3x3 grid centered on (x, y))
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Skip the center cell (x, y) and diagonal neighbors
            if ((dx == 0 && dy == 0)) {
                continue;
            }

            // Calculate neighbor coordinates
            int nx = x + dx;
            int ny = y + dy;
            // Toroidal wrapping
            // If the neighbor is out of bounds, wrap around
            if (nx < 0) { 
                nx += size; 
            }
            if (nx >= size) { 
                nx -= size; 
            }
            if (ny < 0) { 
                ny += size; 
            }
            if (ny >= size) { 
                ny -= size; 
            }
            // Add the value of the neighbor to the sum
            sum += grid[ny][nx];
        }
    }
    //printf("Sum of neighbors for cell (%d, %d): %d\n", x, y, sum);
    return sum;
}

int neighborhood_N(int** grid, int size, int x, int y) {
    int sum = 0;
    
    // Iterate through the Moore neighborhood (3x3 grid centered on (x, y))
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Skip the center cell (x, y) and diagonal neighbors
            if ((dx == 0 && dy == 0) || (abs(dx) + abs(dy) != 1)) {
                continue;
            }

            // Calculate neighbor coordinates
            int nx = x + dx;
            int ny = y + dy;
            // Toroidal wrapping
            // If the neighbor is out of bounds, wrap around
            if (nx < 0) { 
                nx += size; 
            }
            if (nx >= size) { 
                nx -= size; 
            }
            if (ny < 0) { 
                ny += size; 
            }
            if (ny >= size) { 
                ny -= size; 
            }
                
            // Add the value of the neighbor to the sum
            sum += grid[ny][nx];
        }
    }
    //printf("Sum of neighbors for cell (%d, %d): %d\n", x, y, sum);
    return sum;
}

/// @brief Print grid to stdout
/// @param grid pointer to grid to print
/// @param size size of grid side
/// @param gen generation number
/// @details Print grid to stdout, used for debugging/piping
void print_grid(int** grid, int size, int gen){ 
    printf("GEN_%i\n", gen);
    for (size_t i = 0; i < size; i++)
    {
        //printf("Row %d: ", i);
        for (size_t j = 0; j < size; j++)
        {
            printf("%i ", grid[i][j]);
        }
        printf("\n");
    }
}


/// @brief Calculate next cell states simultaneously, conventional game of life approach (in Golly/RLE: B3/S23) \n. Using Moore neighborhood and 2D grid 
/// @param grid grid pointer
/// @param size grid size
/// @param gen generation count number 
void cell_calc(int** grid, int** next_grid, int size, int gen, int neighborhood_type){
    for (size_t y = 0; y < size; y++)
    {
        for (size_t x = 0; x < size; x++)
        {
            // Simulitnaneous calculation for next generation
            int nb_sum;
            if (neighborhood_type == 1) {
                /* code */
                nb_sum = neighborhood_N(grid, size, x, y);
            }
            else if (neighborhood_type == 0)  // Moore neighborhood  
            {
                nb_sum = neighborhood_M(grid, size, x, y);
            }

            int cell = grid[y][x];
            // death
            // by overpopulation
            if (cell == 1 && nb_sum>3)
            {
                next_grid[y][x] = 0;
            }
            // by underpopulation
            if (cell == 1 && nb_sum<2)
            {
                next_grid[y][x] = 0;
            }
            
            // birth
            if (cell == 0 && nb_sum == 3)
            {
                next_grid[y][x] = 1;
            }
            
            // stasis
            if (cell == 1 && (nb_sum == 2 || nb_sum == 3))
            {
                continue;
            }
            if (cell == 0 && nb_sum != 3)
            {
                continue;
            }
        }
        
    }
}

/// @brief Do basic configuration where middle cell = 1
/// @param grid grid pointer
/// @param size size var
void init(int** grid, int** next_grid, int size){
    grid[(int)size/2][(int)size/2] = 1;
}

/// @brief Random initialization of grid
/// @param grid 
/// @param next_grid 
/// @param size 
void init_rnd(int** grid, int** next_grid, int size){
    // Randomly assign cells to be alive or dead
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = rand() % 2; // Randomly assign 0 or 1
        }
    }
}

/// @brief Main function, flow: setup (memory allocation, empty grid), initial conditions, generation calculation and memory cleanup
/// @param argc 
/// @param argv 
int main(int argc, char **argv){
    // Row is "size" cells long -> allocate for length, where each row is array
    int size = 10;
    int gen = 10; // generations to calculate
    int neighborhood_type = 0; // Default neighborhood type: Moore

    if (argc > 1)
    {
        // Help message
        if (strcmp(argv[1], "-h") == 0)
        {
            printf("Usage: %s <neighborhood_type> <size> <generations>\n", argv[0]);
            printf("neighborhood_type: 0 for Moore, 1 for von Neumann (default: 0)\n");
            return 0;
        }
        // Neighborhood type custom: 
        neighborhood_type = atoi(argv[1]);

        // Size custom, default generation count
        if (argc > 2 && atoi(argv[2]) > 0)
        {
            size = atoi(argv[2]);
        }
        // Size and generation count custom
        if (argc > 3 && atoi(argv[3]) > 0)
        {
            gen = atoi(argv[3]);
        }
    }


    // assign base values 0
    int** grid = calloc(size, sizeof(int*));
    int** next_grid = calloc(size, sizeof(int*));
    
    // assign initial config
    // make each item in grid the adress for each row
    for (int i = 0; i<size; i++){
        grid[i] = calloc(size, sizeof(int));
        next_grid[i] = calloc(size, sizeof(int));
        //printf("Check row adress in grid: %p\n",grid[i]);
    }

    // Edge cases
    if (grid == NULL || next_grid == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    //init(grid, next_grid, size);
    init_rnd(grid, next_grid, size);
    print_grid(grid, size, 0);

    // main part
    for (int g = 1; g < gen; g++)
    {
        // calculate next generation
        cell_calc(grid, next_grid, size, g, neighborhood_type);
        
        // print grid for next generation
        print_grid(next_grid, size, g);

        // Overwrite current grid with next grid
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }
    }

    // clean up
    for (int i = 0; i < size; i++) {
        free(grid[i]); // Free each row
        free(next_grid[i]);
    }
    free(grid); // Free the array of pointers
    free(next_grid);
}

