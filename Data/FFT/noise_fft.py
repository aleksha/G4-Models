import numpy as np
import scipy.fftpack as sfft

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


dumpfile = open("dump.txt","r")

fta = []

ll = 0
for line in dumpfile:
    w = (line[:-1]).split(",")
    tch = []
    for ww in w:
        tch.append( float(ww) )
    atch = np.array( tch )
    fta.append ( sfft.rfft( atch )[1:150] ) # as input is real
    ll = ll + 1
    print( "EVENTS: " + str(ll))
dumpfile.close()

for ffta in fta:
    plt.plot( ffta )

#plt.plot( np.angle( fta )[1:100] )
#plt.yscale('log')
plt.savefig('figN.png')
