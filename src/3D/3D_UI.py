from matplotlib import pyplot as plt
from matplotlib import animation
from mpl_toolkits.mplot3d.axes3d import Axes3D
from numpy import array, zeros_like, where
from subprocess import check_output
from os import path

# Global variable to track pause state 
paused_bool = False

# Function to handle key press events
def on_key(event, ani):
    global paused_bool
    if event.key == ' ':
        # Pause or resume the animation
        paused_bool = not paused_bool
        if paused_bool:
            #animation.Animation.pause(ani)
            ani.event_source.stop()
        if not paused_bool:
            #animation.Animation.resume(ani)
            ani.event_source.start()
        

def func3D(gen, ax, gens, size):
    # Clear the current axes
    ax.cla()
    #ax.set_box_aspect([1, 1, 1]) # Aspect ratio is 1:1:1
    
    ax.set_xlim3d(0, size)
    ax.set_ylim3d(0, size)
    ax.set_zlim3d(0, size)

    filled = gens[gen] > 0
    # Define the data for the voxels
    #print(f"Shape of gens[{gen}]: {gens[gen].shape}")
    #print(f"Filled array for generation {gen}:\n{filled}")
    
    ax.voxels(filled, facecolors='white', edgecolors='k')
    #ax.set_aspect('equal')
    ax.set_title(f"Generation {gen}")
    
    #plt.show()

# Return the data in "data" nested list and convert to nparray through pipe
# Output from C program in stdout pipe
def main():
    size = input("Enter size of grid: ")
    if size == "":
        size = 5
    else:
        size = int(size)
    
    generations = input("Enter number of generations: ")
    if generations == "":
        generations = 5
    else:
        generations = int(generations)
    
    tdelay = input("Enter time delay between each frame, in milliseconds: ")
    if tdelay == "":
        tdelay = 250 # default delay
    else:
        tdelay = int(tdelay)
    
    
    s = "{cwd}/3D".format(cwd=path.dirname(path.realpath(__file__)))
    cmd = [s, str(size), str(generations)]
    #print(cmd)
    # Output from C program in stdout pipe
    out = check_output(cmd)
    
    # Stdout handling
    gens = []
    out = out.splitlines()
    l = len(out)
    i = 0
    while i < l:
        line = out[i]
        if not line:
            break
        # Decode bytes to string
        dec = line.decode("utf-8")
        
        if 'GEN' in dec and not (l-i < size):
            # Skip first line (generation number)
            i += 1
            # Print generation number
            print(dec)
            gen_container = []

            # Parse 3D grid / lattice for this generation
            for z in range(0, size):
                # Get lines for each z coordinate
                z_container = []
                for y in range(0, size):
                    # Get values of one row and split
                    dec_line = out[i].decode("utf-8").split()
                    #print(dec_line)
                    # Convert to int
                    dec_line = list(map(int, dec_line))
                    
                    # Append to z_container
                    z_container.append(dec_line)
                    i+= 1
                
                print(f"Parsed z-layer {z}: {z_container}")
                gen_container.append(z_container)
                
            gens.append(array(gen_container))
    """print(f"Parsed generation 0: {gens[0]}")
    print(f"Middle cell: {gens[0][size//2][size//2][size//2]}")"""
        
    #print(f"Number of generations: {len(gens)}")
    #print(f"Shape of first generation: {gens[0].shape}")
    # Create setup for 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d') #111,
    ax.set_aspect('equal')
    ax.set_xlim3d(0, size)
    ax.set_ylim3d(0, size)
    ax.set_zlim3d(0, size)
   
    # Generate animation
    ani = animation.FuncAnimation(fig, func3D, frames=len(gens), fargs=(ax, gens, size), interval=tdelay, blit=False, repeat=False)
    #ani.save('../../ext/3D_animation.gif', writer='imagemagick')
    # Set up the pausing mechanism
    fig.canvas.mpl_connect('key_press_event', lambda event: on_key(event, ani))
    
    plt.show()
            
    

main()
