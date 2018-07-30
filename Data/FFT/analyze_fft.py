import numpy as np
import scipy.fftpack as sfft
from   scipy.stats import norm
import matplotlib.mlab as mlab
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

chan   = 31
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
    fta.append ( sfft.rfft( atch )[1:150] ) # as input is real
    ll = ll + 1
    if not (ll%500): print( "EVENTS: " + str(ll))
dumpfile.close()

data_ch = []
for res in fta:
    data_ch.append( res[chan] )

(mu, sigma) = norm.fit(data_ch)

x = np.array(data_ch)
# the histogram of the data
n, bins, patches = plt.hist(x, 100, normed=1, facecolor='green')
#n, bins, patches = plt.hist(x, n_bins, facecolor='green')

y = mlab.normpdf( bins, mu, sigma)
l = plt.plot(bins, y, 'r--', linewidth=1)

plt.xlabel('Amplitude for frequiency')
plt.ylabel('Events')
plt.title(r'$\mathrm{Histogram\ for\ freq. %d:}\ \mu=%.3f,\ \sigma=%.3f$' %(chan, mu, sigma))


#plt.plot( np.angle( fta )[1:100] )
#plt.yscale('log')
plt.grid(True)
plt.savefig('histN.png')
