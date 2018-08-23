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
in_file = open("g_Cu2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
#    if float(w[3])<300 and float(w[3])>30 :
    if float(w[3])<300 :
        dist   .append(float(w[3]))
#        weights.append(float(w[4]))
#        weights.append( 1./(2.*pi*float(w[3])) )
        weights.append( float(w[4]) / (2.*pi*float(w[3])) )
in_file.close()
#===============================================================================
dist2    = []
weights2 = []
in_file = open("g_Cu3.data","r")
for line in in_file:
    w = line[:-1].split(" ")
#    if float(w[3])<300 and float(w[3])>30 :
    if float(w[3])<300 :
        dist2   .append(float(w[3]))
#        weights.append(float(w[4]))
#        weights.append( 1./(2.*pi*float(w[3])) )
        weights2.append( float(w[4]) / (2.*pi*float(w[3])) )
in_file.close()
#===============================================================================
bins = []
for ii in range(61):
    bins.append(5.*ii)
#===============================================================================
n2, bins2, patches2 = plt.hist( x       = np.array( dist2    ) ,
                             weights = np.array( weights2 ) ,
                             bins    = bins    ,
                             facecolor='blue', alpha=0.5)
#===============================================================================
n, bins, patches = plt.hist( x       = np.array( dist    ) ,
                             weights = np.array( weights ) ,
                             bins    = bins    ,
                             facecolor='green', alpha=0.5)
#===============================================================================
plt.xlabel('Distance, mm')
plt.ylabel('Dose Density, a.u.')
#plt.title('Do')
#plt.axis([40, 160, 0, 0.03])
plt.grid(True)
plt.yscale('log')
plt.savefig("TEMP.png")
#===============================================================================
