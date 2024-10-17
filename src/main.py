import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import imageio

# Display frames/write animation
def display(frames):
    with imageio.get_writer('/../ext/animation.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)

# Make frames of generations
# Handle algorithm here and call appropriate class, depending on CA type
def algo():
    frames = []

    return frames

if __name__ == '__main__':
    f = algo()
    display(f)