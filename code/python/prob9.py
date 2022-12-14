import numpy as np
import pyarma as pa
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from functions import get_data, detector_screen
import sys
import os

# Makes sure we can run in from /code and /code/python
try:
    os.chdir(r'../data')
except:
    os.chdir(r'./data')
# savefile = 'problem9'
# The below is more or less taken directly from assigment text
h = 0.005
dt = 2.5e-5
N = int(1 / h - 1)

x_points = np.linspace(0, 1, N)
y_points = np.linspace(0, 1, N)
x, y = np.meshgrid(x_points, y_points)

bins = ['problem8_double_slit.bin',
        'problem9_single_slit.bin',
        'problem9_triple_slit.bin']

for (i, files) in enumerate(bins):
    if (i == 0):
        savefile = 'problem9_double_slit.pdf'
    else:
        savefile = files.rsplit('.',1)[0] + '.pdf'
    U = get_data(files)

    t_end = dt * len(U[0, :])
    t_points = np.linspace(0, t_end, len(U[0, :]))

    P = np.conjugate(U) * U
    P_cube = np.real(np.reshape(P, (N, N, len(U[0, :]))))
    U_cube = np.reshape(U, (N, N, len(U[0, :])))

    detector_screen(P_cube, y_points, savefile)
