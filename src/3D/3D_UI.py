import sys
from matplotlib import pyplot as plt
from matplotlib import animation
from numpy import array
from subprocess import check_output
from os import getcwd

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
    
    
    s = "{cwd}/3D".format(cwd=getcwd())
    cmd = [s, str(size), str(generations)]
    print(cmd)
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
            print(dec)
            gen_container = []

            # Get all cell values for grid
            # Gen should contain next vertical * horizontal values
            for y in range(1, size+1):
                # Add values of one row
                dec_line = out[i+y].decode("utf-8")
                # Split line into list
                dec_line = dec_line.split()
                # Convert to int
                dec_line = list(map(int, dec_line))
                gen_container.append(dec_line)
                
            gens.append(array(gen_container))
            i += size-1
        i+=1
        
    # Create animation
    fig, ax = plt.subplots()
    ims = []
    # Generate animation
    for i, gen in enumerate(gens):
        im = ax.imshow(gen, cmap='gray', animated=True)
        # Set the title for each frame
        title = ax.text(0.5, 1.05, f'Generation {i}', size=plt.rcParams["axes.titlesize"], ha="center", transform=ax.transAxes)        
        ims.append([im, title])
        i+=1
    
    # Animate the figure    
    ani = animation.ArtistAnimation(fig, ims, interval=tdelay, repeat=False)
    
    # Set up the pausing mechanism
    fig.canvas.mpl_connect('key_press_event', lambda event: on_key(event, ani))
    
    plt.show()
            
    

main()
