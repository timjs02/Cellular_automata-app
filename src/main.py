import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
import imageio
with imageio.get_writer('/path/to/movie.gif', mode='I') as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)




if __name__ == '__main__':
    x = np.linspace(0, 10, 100)
    y = np.sin(x)
    plt.plot(x, y)
    plt.show()