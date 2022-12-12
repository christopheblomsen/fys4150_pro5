import numpy as np
import pyarma as pa
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys

def get_data(problem):
    # Open binary file
    data = pa.cx_mat()
    data.load('test.bin', pa.arma_binary)
    U = np.array(data, dtype=np.clongdouble)
    print(np.shape(U))
    return U


def make_animation(P_cube):
    """
    Function based from project description
    https://anderkve.github.io/FYS3150/book/projects/project5.html
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
    # img.set_norm(norm)

    # Axis labels
    plt.xlabel('x', fontsize=fontsize)
    plt.ylabel('y', fontsize=fontsize)
    plt.xticks(fontsize=fontsize)
    plt.yticks(fontsize=fontsize)

    # Add a colourbar
    cbar = fig.colorbar(img, ax=ax)
    cbar.set_label('P', fontsize=fontsize)
    cbar.ax.tick_params(labelsize=fontsize)

    # Add a text element showing the time
    time_txt = plt.text(0.95, 0.95,
                        't = {:.3e}'.format(t_min),
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
        time_txt.set_text('t = {:.3e}'.format(current_time))

        return img

    # Use matplotlib.animation.FuncAnimation to put it all together
    anim = FuncAnimation(fig, animation, interval=1,
                        frames=np.arange(0, len(P_cube[0, 0, :]), 2),
                        repeat=True, blit=0)

    # Run the animation!
    anim.save('animation.mp4', writer='ffmpeg', fps=30, dpi=300)
    plt.show()



h = 0.005
dt = 2.5e-5
N = int(1 / h - 1)

x_points = np.linspace(0, 1, N)
y_points = np.linspace(0, 1, N)
x, y = np.meshgrid(x_points, y_points)

U = get_data('test.bin')
t_end = dt * len(U[0, :])
print(f't_end:{t_end}')
t_points = np.linspace(0, t_end, len(U[0, :]))

P = np.conjugate(U) * U
P_cube = np.reshape(P, (N, N, len(U[0, :])))
make_animation(np.real(P_cube))
