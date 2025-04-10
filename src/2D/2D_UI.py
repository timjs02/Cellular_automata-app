from matplotlib import pyplot as plt
from matplotlib import animation
from numpy import array
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
        

# Return the data in "data" nested list and convert to nparray through pipe
# Output from C program in stdout pipe
def main():
    size = input("Enter size of grid: ")
    if size == "":
        size = 10
    else:
        size = int(size)
    
    generations = input("Enter number of generations: ")
    if generations == "":
        generations = 5
    else:
        generations = int(generations)
    
    tdelay = input("Enter time delay between each frame, in milliseconds: ")
    if tdelay == "":
        tdelay = 500 # default delay
    else:
        tdelay = int(tdelay)
    
    # Neighborhood type: 
    # M == 0, N == 1
    n_type = input("Enter neighborhood type to use: either Moore (M) / von Neumann (N): ")
    if n_type == "":
        n_type =  0 # default type, von Neumann
    elif n_type == "M":
        n_type = 0
    elif n_type == "N":
        n_type = 1
    
    display_frames = input("Do you want to display the frames during the animation? Significant time increase to be expected (yes/no): ").strip().lower()
    if display_frames not in ['yes', 'no', 'y', 'n']:
        display_frames = 'no'  # default not to displaying frames
    display_frames = display_frames in ['yes', 'y']
    
    s = "{cwd}/2D".format(cwd=path.dirname(path.realpath(__file__)))
    cmd = [s, str(n_type), str(size), str(generations)]
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
            i+= 1
            gen_container = []

            # Get all cell values for grid
            # Gen should contain next vertical * horizontal values
            for y in range(0, size):
                # Add values of one row and split
                dec_line = out[i].decode("utf-8").split()
                # Convert to int
                dec_line = list(map(int, dec_line))
                
                gen_container.append(dec_line)
                i+= 1
                
            gens.append(array(gen_container))
    
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
    ani_path = path.dirname(path.realpath(__file__)) + "/../../ext/2D_animation.gif"
    # Save the animation
    print("saving...")
    ani.save(ani_path, writer='ffmpeg')
    
    # Set up the pausing mechanism
    fig.canvas.mpl_connect('key_press_event', lambda event: on_key(event, ani))
    
    if display_frames:
        # Display the animation
        plt.show()

main()
