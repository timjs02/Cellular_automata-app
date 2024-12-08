import matplotlib.pyplot as plt
cimport numpy as np
import matplotlib as mpl

# TODO: Implement Cython version of CA
# Lines with '#+' are to be replaced with Cython code for performance improvement

# ruleset binary number representation to arbitrary output mapping 
# 2**8, 256 rulesets possible
cdef class Elementary:
    cdef int grid_length
    cdef int[grid_length][grid_length] grid
    cdef int[2] states
    cdef int neighborhood
    self.neighborhood = neighborhood
    
    def __init__(self, grid: np.ndarray, rule: int, grid_len: int):
        self.grid_length = grid_len
        self.grid = grid

        # Elementary Wolfram CA characteristics
        self.states = [0, 1]
        self.neighborhood = 3
        self.rule_table = {}

        self.build_rule_table(rule) #+
        

        # Initial conditions given by user
        assert isinstance(self.grid, np.ndarray), "Grid must be a numpy array"
        # assert dim == grid.ndim, "Dimension of grid must be equal to dim"
        assert grid.ndim == 1, "Only 1D grid is supported"
    
    cdef get_neighborhood(self
    , int cell_pos, np.ndarray grid):
        cdef int[3] nh = []
        
        # Handle edge of array case: first cell, cell_pos-1 is out of bounds, counts as 0
        if cell_pos == 0: #+
            nh = [x for x in [0, grid[cell_pos], grid[cell_pos+1]]]
        # Handle edge of array case: last cell, cell_pos+1 is out of bounds, counts as 0
        elif cell_pos == grid.size-1: #+
            nh = [x for x in [grid[cell_pos-1], grid[cell_pos], 0]] #+
        else:
            nh = [x for x in [grid[cell_pos-1], grid[cell_pos], grid[cell_pos+1]]]
        
        # Check if neighborhood is correct
        if len(nh) != self.neighborhood: #+
            print ("Error in neighborhood function")
            exit(1)

        return *nh
    
    # Get the state of a cell in a new generation (t), as function of state of neighbors in previous gen (t-1)
    cdef int cell_state(self, cell_pos: int, grid: np.ndarray): #+

        # Get the neighborhood of the cell
        cdef int[3] nh = self.get_neighborhood(cell_pos, grid)

        # Get the new state of the cell by checking the ruleset table
        cdef int new_state = self.rule_table.get(tuple(nh), None) # If no rule found, return NULL #+

        if new_state == None: 
            print("Error in cell state, no ruleset state found")
            exit(1)
        return new_state

    # Generate next generation/new grid
    cpdef next_gen(self, old_grid: np.ndarray): #+
        # Fill in the new grid with the new states of the cells
        cdef int[self.grid_length] new_grid = [self.cell_state(i, old_grid) for i in range(0, self.grid_length)]

        return new_grid
    
    cdef void build_rule_table(self, rule):
        # Convert rule number to binary string, padded to 8 bits
        binary_rule = f"{rule:08b}"

        # Create rule table from binary string
        for i in range(8):
            # Convert index to binary and pad to 3 bits
            neighborhood = f"{i:03b}"
            # Convert binary string to tuple of integers
            neighborhood_tuple = tuple(int(bit) for bit in neighborhood) #+
            # Map neighborhood to corresponding output state from binary_rule
            self.rule_table[neighborhood_tuple] = int(binary_rule[7 - i]) #+
            # test
            print(neighborhood_tuple, self.rule_table[neighborhood_tuple]) #+

"""
testing:
ruleset-table: rule 90, or binary rule 01011010
                        7   6   5   4   3   2   1   0
    neihboorhood ->     111 110 101 100 011 010 001 000
    center cell state-> 0   1   0   1   1   0   1   0
"""