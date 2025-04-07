# Cellular Automata

This project is dedicated to creating some Cellular automata that I personally find interesting.
The goal is to simulate in 1-D, 2-D and 3-D.
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
            <li>1D: Wolfram Elementary CA</li>
            <li>2D: Conway's Game of Life</li>
            <li>3D: Crystal Growth 1 (Jason Rampe) as 0-6/1,3/2/N</li>
        </ul>
</ul>

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The software and versions needed:

```
Using Python 3.9.6

1010.6	1053.12		15.0.0 (clang-1500.3.9.4)
Using Apple clang version 15.0.0 (clang-1500.3.9.4)
    Target: arm64-apple-darwin23.3.0
    Thread model: posix
    OS: macOS Sonoma 14.3
    Chip: Apple M1
    XCode: 15.3
Using LLVM version 16.0.0
See requirements.txt for Python modules to install.
```

### Installing

A step by step series of examples that tell you how to get a development and deployment env running on Mac, assuming you have git installed. 
Other versions may still work but should be avoided. 

Step 1: Install correct python version: https://www.python.org/downloads/

Step 2: Install correct clang version
```
until finished
```

Step 3: Clone repository (==repo)
At your desired folder, run:
```
git clone https://github.com/timjs02/Cellular_automata-app.git
```

Step 4: Set up virtual environment for python in the repo base folder
```
example
```

Step 5: Activate virtual environment and install dependencies
```
example
```
Use requirements.txt to install python modules and dependencies
```
python -m pip install -r requirements.txt
```


## Demo

## Deployment
Step 1: Compile C file, for example in 3D. Important: Do not change the path in the repo and the name of the file /src/3D/3D !
```
/path/.../clang -g /path/to/repo/.../Cellular_automata-app/src/3D/3D.c -o /path/to/repo/.../Cellular_automata-app/src/3D/3D
```
Example: 3D
```
/usr/bin/clang -g /path/to/repo/.../Cellular_automata-app/src/3D/3D.c -o /path/to/repo/.../Cellular_automata-app/src/3D/3D
```
Step 2: Run python file, for 3D
```
/path/to/repo/.../Cellular_automata-app/.venv/bin/python /path/to/repo/.../Cellular_automata-app/src/3D/3D_UI.py
```
Step 3: Enter desired inputs for the simulation, where:
- size: Length of one "dimension" or axis
- generations: Number of generations to calculate. Note that needed compute increases with O(n^3) per generation, where n equals size.
- time delay: time between frames in milliseconds

Step 4: Last simulation is stored as "3D_animation.gif" in /ext/

## Approach
<ul>
<li>scripting, algorithm and logic/math in Python</li>
<li>frontend in Javascript (optional:by using three.js/p5.js), play video file using JS </li>
</ul>

## Implementation

### General
<h4>General algorithm for CA:</h4>
<ul>
    <li>Create x-D Grid</li>
    <li>Create initial conditions => gen 0</li>
    <li>Calculate per gen, for every cell at t = f(neighbors at t-1) = tbd ...</li>
    <li>Make frames of gens -> play frames ...</li>
</ul>

### 1D
<h4>Constraints for 1D / Wolfram Elementary CA:</h4>
<ul>
    <li>Cell-Grid: 1-D</li>
    <li>Cell: 1 Square</li>
    <li>States: 2 States -> 0/1</li>
    <li>Neighborhood: Adjascent cells to a cell -> 3 cells total</li>
    <li>cell at t = f(neighbors at t-1) = tbd</li>
</ul>

<h4>General algorithm for 1D / Wolfram Elementary CA:</h4>
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

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Inspiration: https://matplotlib.org/stable/gallery/animation/dynamic_image.html, https://matplotlib.org/stable/gallery/animation/animation_demo.html, https://matplotlib.org/stable/gallery/mplot3d/voxels_numpy_logo.html#sphx-glr-gallery-mplot3d-voxels-numpy-logo-py, https://matplotlib.org/stable/gallery/animation/random_walk.html#sphx-glr-gallery-animation-random-walk-py, https://matplotlib.org/stable/plot_types/3D/voxels_simple.html#sphx-glr-plot-types-3d-voxels-simple-py
* Credit for rules implemented in testing: https://softologyblog.wordpress.com/2019/12/28/3d-cellular-automata-3/
* Readme Template: https://gist.github.com/timjs02/723e52bee7e99c61ab8dd3455d7d65c5

