import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
import os 
from mpl_toolkits.axes_grid1 import make_axes_locatable

# Figures settings
plt.rc('text', usetex=True)
# plt.rc('font', family='Helvetica')

SMALL_SIZE = 15
MEDIUM_SIZE = 18
BIGGER_SIZE = 22

plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
plt.rc('axes', titlesize=SMALL_SIZE)     # fontsize of the axes title
plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
plt.rc('xtick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
plt.rc('ytick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
plt.rc('figure', titlesize=BIGGER_SIZE)  # fontsize of the figure title


# directory of the data
os.chdir(r'./data')



def get_data(problem):
    """
    Loads the binary file and converts it
    to numpy array

    Parameters:
    -----------
    problem:
            binary file created in cpp

    Returns:
            numpy array
    """
    data = pa.cx_mat()
    data.load(problem, pa.arma_binary)
    U = np.array(data, dtype=np.clongdouble)
    return U


def deviation(U, t):
    """
    Take the 2D array (u, time) and calculate
    the total probability deviation and plot 
    it for safety check

    Parameters:
    -----------
    U:
        2D array with all u point and time like (u, t)
    
    t:
        1D array representing the time scale for the plot 
    
    Returns:
        show the deviation plot 
    """

    # calculate the total probability
    prob_u = np.abs(U)**2
    tot_prob_u = np.sum(prob_u, axis=0)
    
    # caculate the deviation
    abs_err = np.abs(tot_prob_u - 1)

    #plot it 
    plt.figure()
    plt.plot(t, abs_err)
    plt.xlabel('Time')
    plt.ylabel('Absolute error')
    plt.title('Absolute error in the total probability')
    plt.show()
    

def colourmap(U, t_step, save=False):
    """
    Plot 3 colourmap for the probability, 
    imaginary and real part 

    Parameters:
    -----------
    U:
        2D array (u, t) 

    t_step:
        the time step we want to plot the colourmap 
        must be an array of int for index

    save:
        put True if we want to save the data set to FALSE

    Returns:
        show the three colourmaps
    """

    #x-y discretization
    M = int(1/ 0.005) + 1
    N = M - 2

    U = U.reshape(N, N, U.shape[1])

    time = np.array([0, 0.001, 0.002])

    for index, t in zip(t_step, time):
        
        # taking the time slice we want 
        u = U[:,:,index]

        # taking the real part 
        u_real = u.real
        u_real /= np.max(u_real)

        # taking the complex part 
        u_im = u.imag
        u_im /= np.max(u_im)
        
        # calculation the probability
        prob = np.abs(u)**2
        prob /= np.max(prob)

        # test_min = np.percentile(U[:,:,index], 1)
        # test_max = np.percentile(U[:,:,index], 99)
        # norm = colors.

        # real plot 
        fig, ax = plt.subplots()
        im = plt.imshow(u_real, cmap='jet')

        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Re(u) at time {}'.format(t))


        # for nicer colorbar
        divider = make_axes_locatable(ax)
        cax = divider.append_axes('right', size='5%', pad=0.05)
        fig.colorbar(im, cax=cax, orientation='vertical')

        if save:
            fig.savefig('real_plot_'+str(t)+'.pdf')

        # complex plot 
        fig, ax = plt.subplots()
        im = plt.imshow(u_im, cmap='jet')

        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Im(u) at time {}'.format(t))


        # for nicer colorbar
        divider = make_axes_locatable(ax)
        cax = divider.append_axes('right', size='5%', pad=0.05)
        fig.colorbar(im, cax=cax, orientation='vertical')

        if save:
            fig.savefig('im_plot_'+str(t)+'.pdf')


        # for probability
        fig, ax = plt.subplots()
        im = plt.imshow(prob, cmap='jet')

        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Probability at time {}'.format(t))

        # for nicer colorbar
        divider = make_axes_locatable(ax)
        cax = divider.append_axes('right', size='5%', pad=0.05)
        fig.colorbar(im, cax=cax, orientation='vertical')

        if save:
            fig.savefig('prob_plot_'+str(t)+'.pdf')


    plt.show()


# load data
data8 = get_data('problem8.bin')

# Time parameters
T = 0.002
dt = 2.5e-5
time = np.arange(0,T, dt)


# verification check 
# deviation(data8, time)

# getting the time for colour map 
time1, = np.where(time == 0.001)[0]

time_stamp = np.array([0, time1, -1])

colourmap(data8, time_stamp, save=True)
