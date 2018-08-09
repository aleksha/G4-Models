#===============================================================================

dump_path = "/home/user/Temp/dump.txt"
show_ch  = 10 # channel to show
show_ch  = 16 # channel to show

show_ev  = 16 # event to show

range_ch = 40
n_bins   = 30
progress = 500
show_progress = True
#===============================================================================
# see for details
# https://docs.scipy.org/doc/scipy/reference/generated/scipy.fftpack.rfft.html#scipy.fftpack.rfft
#===============================================================================
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from   scipy.fftpack import  fft,  ifft
from   scipy.fftpack import rfft, irfft
from   scipy.stats   import norm
from math import pow, sqrt, atan, pi
#===============================================================================
def Arg( x, y ):
    if x > 0             : return atan(y/x)
    if x < 0  and y >= 0 : return atan(y/x)+pi
    if x < 0  and y < 0  : return atan(y/x)-pi
    if x == 0 and y > 0  : return 0.5*pi
    if x == 0 and y == 0 : return 0            # not defined actually
#===============================================================================
print("\n")
dataset = []
event_counter = 0
print("Loading dump file")
dumpfile = open(dump_path,"r")
for line in dumpfile:
    value_str_list = (line[:-1]).split(",")
    value_list = []
    for val in value_str_list:
        value_list.append( float( val ) )
    dataset.append( np.array( value_list ) )
    event_counter = event_counter + 1
    if show_progress:
        if not (event_counter%progress):
            print( "EVENTS LOADED: " + str( event_counter ) )
dumpfile.close()
print("Dataset is loaded ( " + str(event_counter) + " events )" )
print("  dataset -- list of numpy arrays, each entry is event")
#===============================================================================
print("\n")
fft_list = []
event_counter = 0
print("Performing fast Fourier transformation")
for event in dataset:
    fft_list.append( rfft( event ) )
    event_counter = event_counter + 1
    if show_progress:
        if not (event_counter%progress):
            print( "EVENTS LOADED: " + str( event_counter ) )
print("Performing fast Fourier transformation")
print("Fast Fourier transform is done ( " + str(event_counter) + " events )" )
print("  fft_list -- list of numpy arrays (complex numbers), each entry is event")
#===============================================================================
zero_term = []
eRe = []; eIm = []; eAbs = [] ; eAng = []
for evt in fft_list:
    zero_term.append( evt[0] /1500.)
    Re = []; Im = []; Abs = []; Ang = []
    for idx in range(1, len(evt)/2 ):
        Re .append( evt[ 2*idx-1 ]  )
        Im .append( evt[ 2*idx   ]  )
        Abs.append( sqrt( pow(evt[2*idx-1],2) + pow(evt[2*idx],2) ) )
        Ang.append( Arg( evt[2*idx-1], evt[2*idx] ) )
    eRe .append( Re  )
    eIm .append( Im  )
    eAbs.append( Abs )
    eAng.append( Ang )
#===============================================================================
hist_ch = eAng[show_ev]
x = np.array(hist_ch)
n, bins, patches = plt.hist(x, 30, facecolor='blue')
plt.savefig('EVENT.png')
#===============================================================================
hist_ch = []
for evt in eAbs:
    hist_ch.append( evt[show_ch] / 1500. )
x = np.array(hist_ch)
n, bins, patches = plt.hist(x, 30, facecolor='green')
#n, bins, patches = plt.hist(zero_term, 30, facecolor='green')
plt.savefig('HIST.png')
#===============================================================================
mean_val = []
std_dev  = []
v_chan   = []
e_chan   = []
for chan in range(len(eAbs[0])):
    v_chan.append( chan )
    e_chan.append( 0    )
    data_ch = []
    for evt in eAbs:
        data_ch.append( evt[chan] )
    (mu, sigma) = norm.fit(data_ch)
    mean_val.append( mu    )
    std_dev .append( sigma )
plt.errorbar( v_chan, mean_val, xerr = e_chan, yerr = std_dev)
plt.plot( mean_val[:100] )
plt.grid(True)
plt.axis([0, 100, 0, 10000])
#plt.savefig('ABS.png')
plt.savefig('ARG.png')
#===============================================================================
