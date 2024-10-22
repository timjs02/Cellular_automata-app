import numpy as np
import matplotlib.pyplot as plt
#import imageio
import ca_wolfram as ca
import time
import sys

# Make frames of generations
# Handle algorithm here and call appropriate class, depending on Wolfram's CA type
# gen_count: number of generations
# grid dimensions: n
# grids per demension: g
# rule: r
def algo_1d_wolf(inf, gen_count, n, g, r):
    ### Handle initial conditions
    alike = 0
    # Creating dimentional grid
    for d in range(0, n):
        alike = [alike for i in range(g)]

    # Get shape of grid
    #shape = np.shape(alike)
    
    # Handle states
    states = [0, 1] # binary states

    # Class instantiation
    ca_instance = None
    
    # Convert dimentional grid list to numpy array with random 
    #grid = np.random.default_rng().choice(states, size=shape)
    grid = np.array(alike)
    # TODO: Handle random initial conditions, use random bool argument to determine if random or not
    
    # Choose initial conditions
    idx = int(g/2) # middle cell
    grid[idx] = 1

    # Rule determination and class instantiation
    if r < 256:
        ca_instance = ca.Elementary(grid, r)
    else: 
        print("Rule not supported")
        exit(1)

    # Handle finite generation case
    if not inf:
        # Save initial frame at gen 0
        frames = [grid]
        # Generate
        for gen in range(gen_count):
            # Get next generation
            grid = ca_instance.next_gen(grid)
            # Save frame
            frames.append(grid)
        return frames
    
    # Handle infinite case
    else: 
        return None

# Display frames/write animation
def display(frames, genCount, inf, dim):
    if not inf:
        # Display frames, 1. approach
        fig, ax = plt.subplots()
        
        # TODO: understand what is happening here !!!!
        frames = np.array(frames)
        frames = np.expand_dims(frames, axis=0)
        plt.ylabel('Generations')
        plt.xlabel('Grids')
        # currently only displaying last generatid frame
        ax.imshow(frames[0], cmap='binary')
        plt.show()
        
"""
        with imageio.get_writer('/../ext/animation.gif', mode='I') as writer:
            for img in images:
                image = imageio.imread(img)
                writer.append_data(image)"""

if __name__ == '__main__':
    inf = False # infinite case
    genCount = 4000 # number of generations to simulate, including gen 0
    n = 1 # grid dimension
    g = 8000 # grids per demension
    r = int(sys.argv[1]) # rule
    # Start timer
    start = time.time()
    # Get frames
    frames = algo_1d_wolf(inf, genCount, n, g, r)
    # End timer
    end = time.time()
    print("Frames generated, time elapsed: ", end - start, "seconds")
    # Display frames
    display(frames=frames, genCount=genCount, inf=inf, dim=n)

    # TODO: Option for acceleration by using multiprocessing
    # TODO: Implement and check rules 30/110 in Class, implement other rules
    # TODO: Implement random initial conditions from algo_wolf function parameters