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
in_file = open("out.data","r")
for line in in_file:
    w = line[:-1].split(" ")
#    if float(w[3])<300 and float(w[3])>30 :
    if float(w[3])<300 :
        dist   .append(float(w[3]))
#        weights.append( 20. )
#        weights.append(float(w[4]))
#        weights.append( 1./(2.*pi*float(w[3])) )
#        weights.append( float(w[4]) / (2.*pi*float(w[3])) )
in_file.close()
#===============================================================================
bins = []
for ii in range(301):
    bins.append(ii)
#===============================================================================
n, bins, patches = plt.hist( x       = np.array( dist    ) ,
#                             weights = np.array( weights ) ,
                             bins    = bins    ,
                             facecolor='green', alpha=0.75)
#===============================================================================
print( n    )
print( bins )
#===============================================================================
new_n = []
new_bins = []
for idx in range(len(n)):
    new_bins.append( idx*1.)
    new_n.append( 100.*20.*n[idx] / ( pi * ( 1.+2.*idx ) ) )
#new_bins.append( idx*5.)
#===============================================================================
print( new_n    )
#print( bins )
#===============================================================================
plt.clf()
plt.plot(new_bins, new_n)
#===============================================================================
plt.xlabel('Distance, mm')
plt.ylabel('Flux of electrons, 1/(s*cm2)')
#plt.title('Do')
#plt.axis([40, 160, 0, 0.03])
plt.grid(True)
plt.yscale('log')
plt.savefig("TEMP.png")
#===============================================================================
