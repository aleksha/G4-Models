#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi
#===============================================================================
dist    = []
in_file = open("source.data","r")
for line in in_file:
    dist   .append(float(line[:-1]))
in_file.close()
#===============================================================================
bins = []
for ii in range(251):
    bins.append(0.01*ii)
#===============================================================================
n, bins, patches = plt.hist( x       = np.array( dist    ) ,
                             bins    = bins    ,
                             facecolor='blue', alpha=0.55)
#===============================================================================
plt.xlabel('Kinetic Energy, MeV')
plt.ylabel('Events')
#plt.title('Do')
#plt.axis([40, 160, 0, 0.03])
plt.grid(True)
#plt.yscale('log')
plt.savefig("SOURCE.png")
#===============================================================================
