import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
import os 


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


# load data
data_no_slit = get_data('problem7_no_slit.bin')
data_slit = get_data('problem7_double_slit.bin')

print(data_no_slit.shape)
print(data_slit.shape)

# Time parameters 
T = 0.008
dt = 2.5e-5
time = np.arange(0, T, dt)

M = int(1/ 0.005) + 1
N = M - 2
L = N*N

# probablity
prob_no_slit = np.abs(data_no_slit)**2
prob_slit = np.abs(data_slit)**2

# total probability
tot_prob_no_slit = np.sum(prob_no_slit, axis=0)
tot_prob_slit = np.sum(prob_slit, axis=0)

# absolute error 
abs_error = np.abs(tot_prob_no_slit - 1)
abs_error_slit = np.abs(tot_prob_slit - 1)

# plot the absolute error
plt.figure()
plt.plot(time, abs_error, label='No slit')
plt.plot(time, abs_error_slit, label='Double slit')
plt.xlabel('Time')
plt.ylabel('Absolute error')
plt.title('Absolute error in the total probability')
plt.legend()
# plt.savefig('problem7_error.pdf')
plt.show()
