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
weights = []
#in_file = open("Cu_2.data","r")
in_file = open("out.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    if float(w[3])<300 :
#    if float(w[3])<300 and float(w[3])>50 :
        dist   .append(float(w[3]))
#        weights.append(float(w[4]))
        weights.append( 1./(2.*pi*float(w[3])) )
#        weights.append( float(w[4]) / (2.*pi*float(w[3])) )
in_file.close()
#===============================================================================
bins = []
for ii in range(60):
    bins.append(5.*ii)
#===============================================================================
n, bins, patches = plt.hist( x       = np.array( dist    ) ,
                             weights = np.array( weights ) ,
                             bins    = bins    ,
                             facecolor='green', alpha=0.75)
#===============================================================================
plt.xlabel('Distance, mm')
plt.ylabel('Dose Density, a.u.')
#plt.title('Do')
#plt.axis([40, 160, 0, 0.03])
plt.grid(True)
plt.yscale('log')
plt.savefig("DOSE.png")
#===============================================================================
