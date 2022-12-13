"""
A collection of functions used for the python analysis
"""
import numpy as np
import numpy as np
import pyarma as pa
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys

def make_title(savefile):
    """
    Used to make the title for make_colourmap

    Parameters:
    -----------
    savefile:
            string, to determine title

    Returns:
    -----------
            string, the title of plot
    """
    temp = savefile.split('_')[1:]
    if (len(temp) == 2):
        temp[0], temp[1] = temp[1], temp[0]
        ans = '('.join(temp) + ')'
    else:
        ans = temp[0]
    return ans

def get_data(problem):
    """
    Loads the binary file and converts it
    to numpy array

    Parameters:
    -----------
    problem:
            binary file created in cpp

    Returns:
    -----------
            numpy array
    """
    data = pa.cx_mat()
    data.load(problem, pa.arma_binary)
    U = np.array(data, dtype=np.clongdouble)
    return U

def make_colourmap(P_cube, savefile, time_index,
                   time_points, x_points, y_points):
    """
    Modified version of make_animation, but takes
    the snapshot at given time


    Parameters:
    -----------
    P_cube:
            Normalized probability cube over the simulation
    Savefile:
            string that is the suffix to the savefile
    time_index:
            int, containig index of the plotted time
    time_points:
            array containing the time point
    x_points:
            array containing x pos points
    y_points:
            array containing y pos points


    Returns:
    --------
            Nothing, but saves the animation
    """
    # Some settings
    fontsize = 12
    x_min, x_max = x_points[0], x_points[-1]
    y_min, y_max = y_points[0], y_points[-1]

    # Create figure
    fig = plt.figure()
    ax = plt.gca()

    # Create a colour scale normalization according to the max z value in the first frame
    norm = matplotlib.cm.colors.Normalize(
            vmin=0.0, vmax=np.max(P_cube[:, :, time_index]))

    # Plot the first frame
    img = ax.imshow(P_cube[:, :, time_index],
                    extent=[x_min, x_max, y_min, y_max],
                    cmap=plt.get_cmap('jet'),
                    norm=norm)

    # Axis labels
    plt.xlabel('x', fontsize=fontsize)
    plt.ylabel('y', fontsize=fontsize)
    plt.xticks(fontsize=fontsize)
    plt.yticks(fontsize=fontsize)

    # Generate title
    title = make_title(savefile)

    # Add a colourbar
    cbar = fig.colorbar(img, ax=ax, fraction=0.046, pad=0.04)
    cbar.set_label(title, fontsize=fontsize)
    cbar.ax.tick_params(labelsize=fontsize)

    # Add a text element showing the time
    time_txt = plt.text(0.95, 0.95,
                        't = {:.3e} [s]'.format(time_points[time_index]),
                        color='white',
                        horizontalalignment='right',
                        verticalalignment='top',
                        fontsize=fontsize)

    plt.title(title)
    plt.savefig(f'{savefile}_{time_points[time_index]:.3f}.pdf')
    plt.show()


def make_animation(P_cube, savefile, t_points,
                   x_points, y_points, dt):
    """
    Function based from project description
    https://anderkve.github.io/FYS3150/book/projects/project5.html

    Parameters:
    -----------
    P_cube:
            Normalized probability cube over the simulation
    Savefile:
            string that is the suffix to the savefile
    t_points:
            array containing time points
    x_points:
            array containing x pos points
    y_points:
            array containing y pos points
    dt:
            float timestep


    Returns:
    --------
            Nothing, but saves the animation
    """
    # Some settings
    fontsize = 12
    t_min = t_points[0]
    x_min, x_max = x_points[0], x_points[-1]
    y_min, y_max = y_points[0], y_points[-1]

    # Create figure
    fig = plt.figure()
    ax = plt.gca()

    # Create a colour scale normalization according to the max z value in the first frame
    norm = matplotlib.cm.colors.Normalize(
            vmin=0.0, vmax=np.max(P_cube[:, :, 0]))

    # Plot the first frame
    img = ax.imshow(P_cube[:, :, 0],
                    extent=[x_min, x_max, y_min, y_max],
                    cmap=plt.get_cmap('jet'),
                    norm=norm)

    # Axis labels
    plt.xlabel('x', fontsize=fontsize)
    plt.ylabel('y', fontsize=fontsize)
    plt.xticks(fontsize=fontsize)
    plt.yticks(fontsize=fontsize)

    title = ' '.join(savefile.split('_')[1:]).capitalize()
    plt.title(title)

    # Add a colourbar
    cbar = fig.colorbar(img, ax=ax, fraction=0.046, pad=0.04)
    cbar.set_label('P', fontsize=fontsize)
    cbar.ax.tick_params(labelsize=fontsize)

    # Add a text element showing the time
    time_txt = plt.text(0.95, 0.95,
                        't = {:.3e}[s]'.format(t_min),
                        color='white',
                        horizontalalignment='right',
                        verticalalignment='top',
                        fontsize=fontsize)


    # Function that takes care of updating the z data and other things for each frame
    def animation(i):
        # Update z data
        img.set_data((P_cube[:, :, i]))

        # Update the time label
        current_time = t_min + i * dt
        time_txt.set_text('t = {:.3e}[s]'.format(current_time))

        return img

    # Use matplotlib.animation.FuncAnimation to put it all together
    anim = FuncAnimation(fig, animation, interval=1,
                        frames=np.arange(0, len(P_cube[0, 0, :]), 2),
                        repeat=True, blit=0)

    # Run the animation!
    anim.save(f'{savefile}_anim.mp4', writer='ffmpeg', fps=30, dpi=300)
    plt.show()

def detector_screen(P_cube, y_points, savefile,
                    x=0.8, h=0.005, time_point=-1):
    """
    Plots the probability for hitting an imaginary screen
    at point x at time t

    Parameters:
    -----------
    P_cube:
            Normalized probability cube over the simulation
    savefile:
            string that is the suffix to the savefile
    y_points:
            array containing y pos points
    time_point:
            int, index for the corresponding
            default: to last time
    x:
            float, x position
            default: 0.8
    h:
            float, stepsize
            default: 0.005

    Returns:
    --------
            Nothing, but saves the image
    """
    screen_index = int(x/h)
    P = P_cube[screen_index, :, time_point]/np.sum(P_cube[screen_index, :, time_point])
    plt.plot(y_points, P)
    plt.xlabel('y')
    plt.ylabel('Normalised probability')
    plt.savefig(savefile)
    plt.show()
