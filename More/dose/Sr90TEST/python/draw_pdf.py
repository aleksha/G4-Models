#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi
#===============================================================================
dist = []
idx  = []
in_file = open("array.txt","r")
cc = 0
for line in in_file:
    dist.append(float(line[:-1]))
    idx.append(cc)
    cc = cc + 1
in_file.close()
#===============================================================================
bins = []
for ii in range(201):
    bins.append(0.01*ii)
#===============================================================================
plt.plot( np.array( dist  ) )
#===============================================================================
plt.xlabel('Events')
plt.ylabel('Kinetic Energy, MeV')
#plt.title('Do')
#plt.axis([40, 160, 0, 0.03])
plt.grid(True)
#plt.yscale('log')
plt.savefig("SOURCE.png")
#===============================================================================
