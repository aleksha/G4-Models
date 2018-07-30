import numpy as np
import scipy.fftpack as sfft
from   scipy.stats import norm
import matplotlib.mlab as mlab
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

range_ch = 40
n_bins = 30

fta = []
ll = 0
dumpfile = open("/home/user/Temp/dump.txt","r")
for line in dumpfile:
    w = (line[:-1]).split(",")
    tch = []
    for ww in w:
        tch.append( float(ww) )
    atch = np.array( tch )
    fta.append ( sfft.rfft( atch )[1:range_ch] ) # as input is real
    ll = ll + 1
    if not (ll%500): print( "EVENTS: " + str(ll))
dumpfile.close()


mean_val = []
std_dev  = []
for chan in range(range_ch-1):
    data_ch = []
    for res in fta:
        data_ch.append( res[chan] )
    (mu, sigma) = norm.fit(data_ch)
    mean_val.append( mu    )
    std_dev .append( sigma )

#plt.plot( mean_val )
plt.plot( std_dev )
plt.grid(True)
#plt.savefig('meanN.png')
plt.savefig('stdN.png')
