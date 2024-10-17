import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl

# ruleset binary number representation to arbitrary output mapping 
# 2**8, 256 rulesets possible
class Elementary():
    def __init__(self, grid: np.ndarray, dim: int):
        self.grid = grid
        self.dim = dim

        # Elementary Wolfram CA characteristics
        self.states = [0, 1]
        self.neighborhood = 3
        self.rule_table = {}

        # Initial conditions given by user
        assert isinstance(self.grid, np.ndarray), "Grid must be a numpy array"
        assert dim == grid.ndim, "Dimension of grid must be equal to dim"
        assert grid.ndim == 1, "Only 1D grid is supported"
    
    def neighborhood(self, cell_pos: int, grid: np.ndarray):
        nh = []
        coord = [cell_pos-1, cell_pos, cell_pos+1]
        for i in coord:
            nh.append(grid[i])
        
        if not nh or len(nh) != self.neighborhood: 
            print ("Error in neighborhood function")
            exit(1)
        return nh, coord

    # Get the state of a cell in a new generation (t), as function of state of neighbors in previous gen (t-1)
    def cell_state(self, cell_pos: int, grid: np.ndarray):
        new_state = "NULL"

        # Get the neighborhood of the cell
        nbrh, coord = self.neighborhood(cell_pos, grid)

        # Get the new state of the cell
        for (conf, value) in self.rule_table.items():
            if conf == nbrh:
                new_state = value
                break

        if new_state == "NULL": 
            print("Error in cell state, no ruleset state found")
            exit(1)
        return new_state

    # Generate next generation, new grid
    def gen(self, old_grid: np.ndarray):
        grid_length = old_grid.size
        new_grid = np.zeros(grid_length)
        
        # np arrays count from 1 apprently?
        # Fill in the new grid with the new states of the cells
        for i in range(1, grid_length):
            new_grid[i] = self.cell_state(i, old_grid)

        return new_grid

"""
ruleset-table: rule 90, or binary rule 01011010
    neihboorhood ->     111 110 101 100 011 010 001 000
    center cell state-> 0   1   0   1   1   0   1   0
"""
class Rule90(Elementary):
    def __init__(self, rule):
        super().__init__()
        assert rule == 90, "Rule must be 90"
        self.rule = rule
        self.rule_table = {
            [1, 1, 1]: 0,
            [1, 1, 0]: 1,
            [1, 0, 1]: 0,
            [1, 0, 0]: 1,
            [0, 1, 1]: 1,
            [0, 1, 0]: 0,
            [0, 0, 1]: 1,
            [0, 0, 0]: 0
        }

    def rule_appl(self):
        pass