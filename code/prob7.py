import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
import os 



# directory of the data
os.chdir(r'/home/rhuvy/Documents/FYS4150/Projects/fys4150_pro5/code')

# load data
data = pa.cx_mat()
data.load('test_good.bin')
data = np.asarray(data)


T = 0.008
dt = 2.5e-5

M = int(1/ 0.005) + 1
N = M - 2
L = N*N


time = np.arange(0, T, dt)

prob = np.abs(data)**2
print(data.shape)
tot_prob = np.sum(prob, axis=0)

# prob = np.conjugate(data)*data
# tot_prob = np.real(np.sum(prob, axis=0))
print(np.abs(tot_prob -1))
# plt.figure()
# plt.plot(time, tot_prob-1)
# plt.xlabel('Time')
# plt.yticks()
# # plt.ylim(np.min(tot_prob), np.max(tot_prob))
# plt.title('Probability of finding the particle in the box')
# plt.show()
# print(data[:10, 0])

test = np.empty(shape=(N, N, 320))

for i in range(320):
    data[:N-1,i] = test[:N-1, 0, i]
    data
data = data.reshape(N,N, 320)
prob = np.abs(data)**2

# initial condition 
plt.figure()
im = plt.imshow(prob[:,:,0])
plt.show()