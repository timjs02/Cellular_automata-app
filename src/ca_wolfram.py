import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl

# ruleset binary number representation to arbitrary output mapping 
# 2**8, 256 rulesets possible
class Elementary:
    def __init__(self, grid: np.ndarray, rule: int):
        self.grid = grid

        # Elementary Wolfram CA characteristics
        self.states = [0, 1]
        self.neighborhood = 3
        self.rule_table = {}

        self.build_rule_table(rule)

        # Initial conditions given by user
        assert isinstance(self.grid, np.ndarray), "Grid must be a numpy array"
        # assert dim == grid.ndim, "Dimension of grid must be equal to dim"
        assert grid.ndim == 1, "Only 1D grid is supported"
    
    def get_neighborhood(self, cell_pos: int, grid: np.ndarray):
        nh = []
        coord = []
        # Handle edge of array case: first cell
        if cell_pos == 0: 
            coord = [cell_pos, cell_pos+1]
            nh.append(0) # cell_pos-1 is out of bounds, counts as 0
            for i in coord:
                nh.append(grid[i])
        # Handle edge of array case: last cell
        elif cell_pos == grid.size-1:
            coord = [cell_pos-1, cell_pos]
            for i in coord:
                nh.append(grid[i])
            nh.append(0) # cell_pos+1 is out of bounds, counts as 0
            
        else:
            coord = [cell_pos-1, cell_pos, cell_pos+1]
            for i in coord:
                nh.append(grid[i])
        
        # Check if neighborhood is correct
        if not nh or len(nh) != self.neighborhood: 
            print ("Error in neighborhood function")
            exit(1)
        return nh, coord

    # Get the state of a cell in a new generation (t), as function of state of neighbors in previous gen (t-1)
    def cell_state(self, cell_pos: int, grid: np.ndarray):

        # Get the neighborhood of the cell
        nbrh, coord = self.get_neighborhood(cell_pos, grid)

        # Get the new state of the cell by checking the ruleset table
        new_state = self.rule_table.get(tuple(nbrh), "NULL") # If no rule found, return NULL

        if new_state == "NULL": 
            print("Error in cell state, no ruleset state found")
            exit(1)
        return new_state

    # Generate next generation/new grid
    def next_gen(self, old_grid: np.ndarray):
        grid_length = old_grid.size
        new_grid = np.zeros(grid_length)

        # Fill in the new grid with the new states of the cells
        for i in range(0, grid_length):
            new_grid[i] = self.cell_state(i, old_grid)

        return new_grid
    
    def build_rule_table(self, rule):
        # Convert rule number to binary string, padded to 8 bits
        binary_rule = f"{rule:08b}"

        # Create rule table from binary string
        for i in range(8):
            # Convert index to binary and pad to 3 bits
            neighborhood = f"{i:03b}"
            # Convert binary string to tuple of integers
            neighborhood_tuple = tuple(int(bit) for bit in neighborhood)
            # Map neighborhood to corresponding output state from binary_rule
            self.rule_table[neighborhood_tuple] = int(binary_rule[7 - i])
            # test
            print(neighborhood_tuple, self.rule_table[neighborhood_tuple])

"""
testing:
ruleset-table: rule 90, or binary rule 01011010
    neihboorhood ->     111 110 101 100 011 010 001 000
    center cell state-> 0   1   0   1   1   0   1   0
"""