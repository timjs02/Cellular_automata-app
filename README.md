<h1>Cellular automata</h1>
This project is dedicated to creating some Cellular automata that I personally find interesting.
The goal is to scale from a 1-D example, to 3x 2-D examples and 2x 3-D examples, if my computer can handle it.

<h4>Program structure: </h4>
<ul>
<li>scripting, algorithm and logic/math in Python</li>
<li>frontend in Javascript (optional:by using three.js/p5.js), play video file using JS </li>
</ul>
<h4>Charasteristics of a Cellular automata (=CA):</h4>
<ul>
    <li>A grid of cells (1-D, 2-D, 3-D)</li>
    <li>Each cell is an entity that:
        <ul>
            <li>exists in one of a number of states</li>
            <li>has a neighborhood</li>
        </ul>
    </li>
    <li><h4>Rulesets:</h4></li>
        <ul>
            <li>1-D example: Wolfram Elementary CA</li>
            <li>Conway's Game of Life</li>
            <li>--</li>
            <li>--</li>
            <li>---</li>
            <li>---</li>
        </ul>
</ul>
<h4>General algorithm for CA:</h4>
<ul>
    <li>Create x-D Grid</li>
    <li>Create initial conditions => gen 0</li>
    <li>Calculate per gen, for every cell at t = f(neighbors at t-1) = tbd ...</li>
    <li>Make frames of gens -> play frames ...</li>
</ul>

<h4>Pseudocode:</h4>

<code>

    // neighborhood calculation, tbd how to compute neighborhood
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

    func cell_state(cell_pos, grid):
        new_state = NULL
        ruleset = [(neighborhood configuration, next generation value for center cell), ...]
        
        nh, crd = neighb(cell_pos, grid)
        for (conf, value) in ruleset:
            if conf == nh: 
                new_state = value
        
        if new_state == NULL: throw error
        return new_state
        
    func next_gen(old_grid):
        for i to grid length - 1:
            for j to grid length-1: 
                ...
                new_grid[i][j][...] = cell_state((i, j, ...), old_grid)
        return new_grid
    
    # Make frames of generations
    # Handle algorithm here and call appropriate class, depending on CA type
    # genCount: number of generations to simulate
    # grid dimensions: n
    # grids per demension: g
    # rule: r
    func algo(inf, genCount, n, g, r):
        gen = 0 // current generation
        gens = [] // generation series until generations var reached (generations - 1 = gens max index)
        
        # Create empty dimentional grid with n, g vars
        ...

        # Handle rule determination and class instantiation
        if r == some rule number:
            # Handle states
            states = [...] to use

            # Create random initial conditions
            grid = numpy array, where shape = np.shape(grid) and states is the number pool for rng

        # Generate finite generations
        if not inf:
            while gen < genCount:
                gen = gen + 1
                grid = next_gen(grid)
                gens.append(grid)
            return gens
        else:
            # Note sure how to solve yet
            pass

    func display(frames, inf, gCount):
        if not inf:
            1. graphics_object = func(frames, frames = gCount)
            animation =  animate(graphics_object)
            animation.play
            or approach nr.
            2. graphics_object = func(frames, frames = gCount)
            fileReader = readStream(graphics_object).data
            file = "path/to/file.ani"
            if writeStream(file, fileReader) finished writing:
                play(file)
        else:
            make gens to certain high number

    func main():
        n = grid_dimension
        g = grids_per_dimension
        grid = [0 for i to g] * n
        arr = [initial conditions]
        grid = arr
        
        // generation handling 
        inf = bool 
        gen_c = generation count to reach
        frames = algo(inf, genCount, n, g, r)
        display(frames, inf, gen_c)
</code>

_________________________________________________

<h4>Constraints for Wolfram Elementary CA:</h4>
<ul>
    <li>Cell-Grid: 1-D</li>
    <li>Cell: 1 Square</li>
    <li>States: 2 States -> 0/1</li>
    <li>Neighborhood: Adjascent cells to a cell -> 3 cells total</li>
    <li>cell at t = f(neighbors at t-1) = tbd</li>
</ul>

<h4>General algorithm for Wolfram Elementary CA:</h4>
<ul>
    <li>Create 1-D Grid</li>
    <li>Initialize initial conditions => gen 0, e.g. center cell = 1</li>
    <li>Calculate gen 1, the state of each cell = f(neighborhood at t-1) = binary number representation to arbitrary output mapping (2**8, 256 rulesets possible with just this definition)</li>
</ul>

<h4>ruleset-table: rule 90, or binary rule 01011010</h4>
<ul>
    <li>neihboorhood -> 111 110 101 100 011 010 001 000</li>
    <li>center cell state-> 0 1 0 1 1 0 1 0</li>
</ul>

<h4>other rulesets: (link...)</h4>

____________________________________________________________________________________
<h4>Ambitions for the future</h4>
<ul>
    <li>logic/math in MATLAB (maybe C?)</li>
    <li>scripting in Python</li>
    <li>frontend in three.js/p5.js</li>
</ul>
