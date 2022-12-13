import pyarma as pa
import numpy as np
import matplotlib.pyplot as plt

def get_data(problem):
    # Open binary file
    data = pa.cx_mat()
    data.load(problem, pa.arma_binary)
    U = np.array(data, dtype=np.clongdouble)
    print(np.shape(U))
    return U

U = get_data('test.bin')
U = np.array(U)

U_time = pa.cx_mat()
