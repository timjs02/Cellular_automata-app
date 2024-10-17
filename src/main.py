import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import imageio

def display():
    with imageio.get_writer('/../ext/animation.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)

if __name__ == '__main__':
    pass