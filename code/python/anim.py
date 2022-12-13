"""
Makes animations of the probability out of arma binary files

Run

python anim.py binary_data.bin animation_prefix
"""


import numpy as np
import pyarma as pa
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys
from functions import get_data, make_animation

problem = sys.argv[1]
savefile = sys.argv[2]

# The below is more or less taken directly from assigment text
h = 0.005
dt = 2.5e-5
N = int(1 / h - 1)

x_points = np.linspace(0, 1, N)
y_points = np.linspace(0, 1, N)
x, y = np.meshgrid(x_points, y_points)

U = get_data(problem)
t_end = dt * len(U[0, :])
print(f't_end:{ t_end}')
t_points = np.linspace(0, t_end, len(U[0, :]))

P = np.conjugate(U) * U
P_cube = np.reshape(P, (N, N, len(U[0, :])))
make_animation(np.real(P_cube), savefile, t_points,
               x_points, y_points, dt)
