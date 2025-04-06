#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


/// @param lattice Pointer to the lattice
/// @param size Size of the lattice (assuming square lattice)
/// @param x x coordinate
/// @param y y coordinate
/// @return Number of alive neighbors
int neighborhood(int*** lattice, int size, int x, int y, int z) {
    int sum = 0;
    
    // Iterate through the Moore neighborhood (3x3 lattice centered on (x, y, z))
    
    for (int dz = -1; dz <= 1; dz++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++)
            {
                // Skip the center cell (x, y) itself
                if (dx == 0 && dy == 0 && dz == 0) {
                    continue;
                }

                // Calculate neighbor coordinates
                int nx = x + dx;
                int ny = y + dy;
                int nz = z + dz;

                // Check if the neighbor is within bounds
                if ((nx >= 0 && nx < size && ny >= 0 && ny < size && nz >= 0 && nz < size)) {
                    // Add the value of the neighbor to the sum
                    sum += lattice[nz][ny][nx];
                }
            }
        }
    }
    //printf("Sum of neighbors for cell (%d, %d): %d\n", x, y, sum);
    return sum;
}

/// @brief Print lattice to stdout
/// @param lattice pointer to lattice to print
/// @param size size of lattice side
/// @param gen generation number
/// @details Print lattice to stdout, used for debugging/piping
void print_lattice(int*** lattice, int size, int gen){ 
    printf("GEN_%i\n", gen);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            //printf("Row %d: ", j);
            for (size_t l = 0; l < size; l++)
            {
                printf("%i ", lattice[i][j][l]);
            }
            printf("\n");
        }
        
    }
}


/// @brief Calculate next cell states simultaneously, conventional game of life approach (in Golly/RLE: B3/S23) \n. Using Moore neighborhood and 2D lattice 
/// @param lattice lattice pointer
/// @param size lattice size
/// @param gen generation count number 
void cell_calc(int*** lattice, int*** next_lattice, int size, int gen){
    for (size_t z = 0; z < size; z++)
    {
        for (size_t y = 0; y < size; y++)
        {
            for (size_t x = 0; x < size; x++)
            {
                // Simulitnaneous calculation for next generation
                int nb_sum = neighborhood(lattice, size, x, y, z);

                int cell = lattice[z][y][x];
                // death
                // by overpopulation
                if (cell == 1 && nb_sum>3)
                {
                    next_lattice[z][y][x] = 0;
                }
                // by underpopulation
                if (cell == 1 && nb_sum<2)
                {
                    next_lattice[z][y][x] = 0;
                }
                
                // birth
                if (cell == 0 && nb_sum == 3)
                {
                    next_lattice[z][y][x] = 1;
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
}

/// @brief Do basic configuration where middle cell = 1
/// @param lattice lattice pointer
/// @param size size var
void init(int*** lattice, int*** next_lattice, int size){
    lattice[(int)size/2][(int)size/2][(int)size/2] = 1;
}

/// @brief Random initialization of lattice
/// @param lattice 
/// @param next_lattice 
/// @param size 
void init_rnd(int*** lattice, int*** next_lattice, int size){
    // Randomly assign cells to be alive or dead
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int l = 0; l < size; l++)
            {
                lattice[i][j][l] = rand() % 2; // Randomly assign 0 or 1
            }
        }
    }
}

/// @brief Main function, flow: setup (memory allocation, empty lattice), initial conditions, generation calculations and memory cleanup
/// @param argc 
/// @param argv 
int main(int argc, char **argv){
    // Row is "size" cells long -> allocate for length, where each row is array
    int size = 5;
    int gen = 5; // generations to calculate
    if (argc > 1)
    {
        // Size custom, default generation count
        if (argc == 2 && atoi(argv[1]) > 0)
        {
            size = atoi(argv[1]);
        }
        // Help message
        else if (argv[1] == "-h")
        {
            printf("Usage: %s <size> <generations>\n", argv[0]);
            return 0;
        }
        // Size and generation count custom
        else if (argc > 2)
        {
            if (atoi(argv[1]) > 0) size = atoi(argv[1]);
            if (atoi(argv[2]) > 0) gen = atoi(argv[2]);
        }
    }


    // assign base values 0
    int*** lattice = calloc(size, sizeof(int**)); // z
    int*** next_lattice = calloc(size, sizeof(int**));
    
    // assign initial config
    // make each item in lattice the adress for each row
    for (int i = 0; i<size; i++){
        lattice[i] = calloc(size, sizeof(int*)); // y
        next_lattice[i] = calloc(size, sizeof(int*));
        //printf("Check row adress in lattice: %p\n",lattice[i]);
        for (int j = 0; j < size; j++)
        {
            lattice[i][j] = calloc(size, sizeof(int)); // x
            next_lattice[i][j] = calloc(size, sizeof(int)); // x
        }
        
    }
    

    // Edge cases
    if (lattice == NULL || next_lattice == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    init(lattice, next_lattice, size);
    //init_rnd(lattice, next_lattice, size);
    print_lattice(lattice, size, 0);

    // main part
    for (int g = 1; g < gen; g++)
    {
        // calculate next generation
        cell_calc(lattice, next_lattice, size, g);
        
        // print lattice for next generation
        print_lattice(next_lattice, size, g);

        // Overwrite current lattice with next lattice
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int l = 0; l < size; l++)
                {
                    lattice[i][j][l] = next_lattice[i][j][l];
                }
            }
        }
    }

    // clean up
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            free(lattice[i][j]); // Free each cell
            free(next_lattice[i][j]);
        }
        free(lattice[i]); // Free each row
        free(next_lattice[i]);
    }
    free(lattice); // Free the array of pointers
    free(next_lattice);
}

