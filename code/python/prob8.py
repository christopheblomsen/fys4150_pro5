import numpy as np
import pyarma as pa
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from functions import get_data, make_colourmap
import sys
import os

try:
    os.chdir(r'./data')
except:
    os.chdir(r'../data')

savefile = ['problem8_P', 'problem8_U_Re', 'problem8_U_Im']
# The below is more or less taken directly from assigment text
h = 0.005
dt = 2.5e-5
N = int(1 / h - 1)

x_points = np.linspace(0, 1, N)
y_points = np.linspace(0, 1, N)
x, y = np.meshgrid(x_points, y_points)

U = get_data('problem8_double_slit.bin')

t_end = dt * len(U[0, :])
t_points = np.linspace(0, t_end, len(U[0, :]))

P = np.conjugate(U) * U
P_cube = np.reshape(P, (N, N, len(U[0, :])))
U_cube = np.reshape(U, (N, N, len(U[0, :])))

print(f'Shape {np.shape(P_cube)}')
print(P_cube[0, 0, 0])

time_index = np.where(abs(0.001-t_points)<1.3e-5)[0][0]

time_indices = [0, time_index, -1]

for index in time_indices:
    make_colourmap(np.real(P_cube), savefile[0], index,
                   t_points, x_points, y_points)
    make_colourmap(np.real(U_cube), savefile[1], index,
                   t_points, x_points, y_points)
    make_colourmap(np.imag(U_cube), savefile[2], index,
                   t_points, x_points, y_points)
