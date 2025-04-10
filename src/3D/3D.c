#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>


/// @param lattice Pointer to the lattice
/// @param size Size of the lattice (assuming square lattice)
/// @param x x coordinate
/// @param y y coordinate
/// @return Number of alive neighbors
int neighborhood_M(int*** lattice, int size, int x, int y, int z) {
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
                if (nz < 0) { 
                    nz += size; 
                }
                if (nz >= size) { 
                    nz -= size; 
                }

                // Add the value of the neighbor to the sum
                sum += lattice[nz][ny][nx];
                
            }
        }
    }
    //printf("Sum of neighbors for cell (%d, %d): %d\n", x, y, sum);
    return sum;
}

/// @brief Calculate the number of alive neighbors in a 3D von Neumann neighborhood
/// @param lattice Pointer to the lattice
/// @param size Size of the lattice (assuming square lattice)
/// @param x x coordinate
/// @param y y coordinate
/// @return Number of alive neighbors
int neighborhood_N(int*** lattice, int size, int x, int y, int z) {
    int sum = 0;
    
    // Iterate through the von Neuman neighborhood ("cross" lattice centered on (x, y, z))
    
    for (int dz = -1; dz <= 1; dz++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++)
            {
                // Skip the center cell (x, y) and diagonal neighbors
                if ((dx == 0 && dy == 0 && dz == 0) || (abs(dx) + abs(dy) + abs(dz) != 1)) {
                    continue;
                }

                // Calculate neighbor coordinates
                int nx = x + dx;
                int ny = y + dy;
                int nz = z + dz;
                
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
                if (nz < 0) { 
                    nz += size; 
                }
                if (nz >= size) { 
                    nz -= size; 
                }
                
                // Add the value of the neighbor to the sum
                sum += lattice[nz][ny][nx];
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

/// @brief Calculate next cell states simultaneously \n. Using Moore neighborhood and 3D lattice. Crystal Growth 1 (Jason Rampe) 0-6/1,3/2/N
/// @param lattice lattice pointer
/// @param size lattice size
/// @param gen generation count number 
void cell_calc(int*** lattice, int*** next_lattice, int size, int gen, int neighborhood_type){
    for (size_t z = 0; z < size; z++)
    {
        for (size_t y = 0; y < size; y++)
        {
            for (size_t x = 0; x < size; x++)
            {
                // Simultaneous calculation for next generation
                int nb_sum;
                if (neighborhood_type == 1) {
                    nb_sum = neighborhood_N(lattice, size, x, y, z);
                }
                if (neighborhood_type == 0) {
                    nb_sum = neighborhood_M(lattice, size, x, y, z);
                }

                int cell = lattice[z][y][x];

                // stasis: alive cell persists for case, otherwise dead
                if (cell == 1 && (nb_sum >= 0 && nb_sum <= 6))
                {
                    continue;
                } else
                {
                    // death
                    next_lattice[z][y][x] = 0;
                }
                
                // birth
                /*if (cell == 0 && ((nb_sum >= 13 && nb_sum <= 14) || (nb_sum >= 17 && nb_sum <= 19)))
                {
                    next_lattice[z][y][x] = 1;
                }
                */
                if (cell == 0 && ((nb_sum == 1) || (nb_sum == 3)))
                {
                   next_lattice[z][y][x] = 1;
                }

                // death
                // by overpopulation
                /*
                if (cell == 1 && nb_sum>2)
                {
                    next_lattice[z][y][x] = 0;
                }
                // by underpopulation
                if (cell == 1 && nb_sum<1)
                {
                    next_lattice[z][y][x] = 0;
                }
                */
            }
        }
    }
}

/// @brief Do basic configuration where middle cell = 1
/// @param lattice lattice pointer
/// @param size size var
void init(int*** lattice, int size){
    int mid = size/2;
    lattice[mid][mid][mid] = 1;
    //printf("Initial cell: %i\n", lattice[mid][mid][mid]);
}

/// @brief Assign a 3D cross pattern
/// @param lattice 
/// @param size 
void init_cross(int*** lattice, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int l = 0; l < size; l++)
            {
                if (i == size/2 || j == size/2 || l == size/2)
                {
                    lattice[i][j][l] = 1;
                }
                else
                {
                    lattice[i][j][l] = 0;
                }
            }
        }
    }
}

/// @brief Random initialization of lattice
/// @param lattice 
/// @param next_lattice 
/// @param size 
void init_rnd(int*** lattice, int size){
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

/// @brief Create configuration where a certain area in lattice is randomly assigned: from 4/8 to 5/8 of the size, so 1/4 of the lattice volume
/// @param lattice 
/// @param size 
void init_rnd1(int*** lattice, int size){
    for (int i = 4*size/8; i < 5*size/8; i++) {
        for (int j = 4*size/8; j < 5*size/8; j++) {
            for (int l = 4*size/8; l < 5*size/8; l++)
            {
                lattice[i][j][l] = rand() % 2; // Randomly assign 0 or 1
            }
        }
    }
}

/// @brief Fill the entire lattice with 1s
/// @param lattice 
/// @param size 
void init_fill(int*** lattice, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int l = 0; l < size; l++)
            {
                lattice[i][j][l] = 1;
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
    int neighborhood_type = 1; // Default neighborhood type: von Neumann

    if (argc > 1)
    {
        // Help message
        if (strcmp(argv[1], "-h") == 0)
        {
            printf("Usage: %s <neighborhood_type> <size> <generations>\n", argv[0]);
            printf("neighborhood_type: 0 for Moore, 1 for von Neumann (default: 1)\n");
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

    //init_rnd(lattice, size);
    init_rnd1(lattice, size);
    //init_cross(lattice, size);
    //init_fill(lattice, size);
    print_lattice(lattice, size, 0);

    // main part
    for (int g = 1; g < gen; g++)
    {
        // calculate next generation
        cell_calc(lattice, next_lattice, size, g, neighborhood_type);
        
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

