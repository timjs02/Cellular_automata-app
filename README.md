This project is dedicated to creating some Cellular automata that I personally find interesting.
The goal is to scale from a 1-D example, to 3x 2-D examples and 2x 3-D examples, if my computer can handle it.

Structure: 
- scripting, algorithm and logic/math in Python
- frontend in Javascript (optional:by using three.js/p5.js), play video file using JS

Logic:
    Charasteristics of a Cellular automata (=CA):
    - A grid of cells (1-D, 2-D, 3-D)
    - Each cell is an entity that:
        - exists in one of a number of states
        - has a neighborhood
    - Cell state at time t = function f(neighborhood states at time t-1)
    -> Time is expressed as discrete time steps, called generations

    Rulesets:
        -1-D example: Wolfram Elementary CA
        --Conway's Game of Life
        --
        --
        ---
        ---
General algorithm for CA:
- Create x-D Grid
- Create initial conditions => gen 0
- Calculate per gen, for every cell at t = f(neighbors at t-1) = tbd ...
- Make frames of gens -> play frames ...
- Pseudocode:
-     // neighborhood calculation, tbd how to compute neighborhood
      func neighb(cell_pos, grid):
        x, y, .. = cell_pos
        // tbd, depends on how neighborhood is defined. Wolfram's def.: adjacent cells
        coordinates = [(x-1, y, ...), (x-1, y-1, ...), (x, y, ...), ...]
        nh = []
        for i in coordinates:
            nh.append(grid value at i)
        ... error handling ...
        return nh, coordinates
    
    /*
    // To be used if ruleset uses mathematical calculation
    // In contrast, Wolfram's CA use arbitrary rules defined beforehand
    - func ruleset_calc(nbr):
        return new state
    */

    // cell state as function of the neighborhood in gen with t - 1
    - func cell_state(cell_pos, grid):
    -     new_state = NULL
          ruleset = [(neighborhood configuration, next generation value for center cell), ...]
        
          nh, crd = neighb(cell_pos, grid)
            for (conf, value) in ruleset:
                if conf == nh: 
                    new_state = value
        
          if new_state == NULL: throw error
          return new_state


    - func gen(old_grid):
    -     for i to grid length - 1:
            for j to grid length-1: 
                ...
                    new_grid[i][j][...] = cell_state((i, j, ...), old_grid)
          return new_grid
    
    func display(grid, generations, inf, dim, gcount):
        if not inf:
            gen = 0 // current generation
            gens = [] // generation series until generations var reached (generations - 1 = gens max index)

            while gens.length < generations - 1:
                grid = gen(grid)
                gens.append(grid)

            1. graphics_object = func(gens, frames = generations)
            animation =  animate(graphics_object)
            animation.play
            or approach nr.
            2. graphics_object = func(gens, frames = generations)
            fileReader = readStream(graphics_object).data
            file = "path/to/file.ani"
            if writeStream(file, fileReader) finished writing:
                play(file)
        else:
            make gens to certain high number
            while animation playing, make more gens -> ...


    - func main() -> graphics object to display/frame for animation:
        n = grid_dimension
        g = grids_per_dimension
        grid = [0 for i to g] * n
        arr = [initial conditions]
        grid = arr
        
        // generation handling 
        inf = bool 
        gen_c = generation count to reach
        
        if inf:
        // infinite generations
        display(grid, 0, inf, n, g)
        else:
        display(grid, gen_c, inf, n, g)


        





Constraints for Wolfram Elementary CA:
- Cell-Grid: 1-D
- Cell: 1 Square
- States: 2 States -> 0/1
- Neighborhood: Adjascent cells to a cell -> 3 cells total
- cell at t = f(neighbors at t-1) = tbd

General algorithm for Wolfram Elementary CA:
- Create 1-D Grid
- Initialize initial conditions => gen 0, e.g. center cell = 1
- Calculate gen 1, the state of each cell = f(neighborhood at t-1) = 
    binary number representation to arbitrary output mapping (2**8, 256 rulesets possible with just this definition)

ruleset-table: rule 90, or binary rule 01011010
    neihboorhood ->     111 110 101 100 011 010 001 000
    center cell state-> 0   1   0   1   1   0   1   0

other rulesets: (link...)





____________________________________________________________________________________
Ambition for future:
- logic/math in MATLAB (maybe C?)
- scripting in Python
- frontend in three.js/p5.js
