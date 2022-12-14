import numpy as np
import pyarma as pa
import matplotlib.pyplot as plt
import os

try:
    os.chdir('./input_files')
except:
    os.chdir('../input_files')

V = pa.mat()
V.load('double_slit.csv', pa.csv_ascii)
V = np.array(V).T

plt.xlabel('x[pixels]')
plt.ylabel('y[pixels]')
plt.imshow(V, origin='lower', cmap='copper')
plt.savefig('double_slit.pdf')
plt.show()
