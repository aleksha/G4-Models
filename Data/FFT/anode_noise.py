#===============================================================================
# see for details
# https://docs.scipy.org/doc/scipy/reference/generated/scipy.fftpack.rfft.html#scipy.fftpack.rfft
#===============================================================================
dump_file_path = "/home/user/Temp/dump.txt"
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
class anode_noise:
    """Class, which containg info about noise using calibration sample 
       obtained with pulse generator"""

    def __init__(self, dump_path):
        """Load csv dump, make fft (half shorten) as real input"""
        print("Loading anode dump file")
        self.path = dump_path
        self.dataset = []
        dumpfile = open(self.path,"r")
        self.channels = 0
        for line in dumpfile:
            value_str_list = (line[:-1]).split(",")
            if(self.channels == 0 ):
                self.channels = len( value_str_list )
                print("CHANNELS : " + str(self.channels))
            value_list = []
            for val in value_str_list:
                value_list.append( float( val ) )
            self.dataset.append( np.array( value_list ) )
        dumpfile.close()
        fft_list = []
        print("Performing fast Fourier transformation")
        for event in self.dataset:
            fft_list.append( fft( event )[0:self.channels/2] )
        self.fftset = fft_list

    def draw_event(self, num, fig_name = "EVENT.png"):
        """Draw event number num into figure fig_name"""
        plt.plot( self.dataset[num] )
        plt.grid( True )
        plt.xlabel("time, ch.")
        plt.ylabel("val, a.u.")
        plt.title(r'Signal for EVENT %d' %(num))
        plt.savefig( fig_name )
        print("Time spectrum for event " + str(num) + " into " + fig_name )
        plt.clf()

    def draw_spectrum(self, num, fig_name = "SPECTRUM.png"):
        """Draw absolute value of frequiency spectrum"""
        plt.plot( np.abs( self.fftset[num][1:] ) )
        plt.grid( True )
        plt.xlabel("freq., 1/ch.")
        plt.ylabel("val, a.u.")
        plt.title(r'Spectrum for EVENT %d' %(num))
        plt.savefig( fig_name )
        print("Distribution of absolute value ( ev = " + str(num) +  " ) to " + fig_name )
        print(" (zero term substructed)")
        plt.clf()

    def hist_abs(self, chan, fig_name = "ABS_VAL.png"):
        """Distribution of abs. val. for frequency channel for all events"""
        datos = []
        for evt_fft in self.fftset:
            datos.append( np.abs( evt_fft[chan] ) )
        n, bins, patches = plt.hist(datos, 30, facecolor='green')
        plt.grid( True )
        plt.xlabel("abs value")
        plt.ylabel("events")
        plt.title(r'Distribution for FREQ %d' %(chan))
        plt.savefig( fig_name )
        print("Distribution of absolute values for all events ( freq. = " + str(chan) + " ) saved into " + fig_name )
        plt.clf()

    def hist_arg(self, chan, fig_name = "ARG_VAL.png"):
        """Distribution of phase for frequency channel for all events"""
        datos = []
        for evt_fft in self.fftset:
            datos.append( np.angle( evt_fft[chan] ) )
        n, bins, patches = plt.hist(datos, 30, facecolor='green')
        plt.grid( True )
        plt.xlabel("complex phase")
        plt.ylabel("events")
        plt.title(r'Distribution for FREQ %d' %(chan))
        plt.savefig( fig_name )
        print("Distribution of compex phase for all events ( freq. = " + str(chan) + " ) saved into " + fig_name )
        plt.clf()

    def corr_abs(self, chan1, chan2, fig_name = "ABS_CORR.png"):
        """Scatter plot for two complex phases"""
        datos1 = []
        datos2 = []
        for evt_fft in self.fftset:
            datos1.append( np.abs( evt_fft[chan1] ) )
            datos2.append( np.abs( evt_fft[chan2] ) )
        plt.scatter(datos1, datos2, s=10, c = "red", alpha=0.5)
        plt.grid( True )
        plt.xlabel("abs. val. for freq. " + str(chan1))
        plt.ylabel("abs. val. for freq. " + str(chan2))
        plt.title(r'Correlation of abs. val. between %d and %d' %(chan1,chan2))
        plt.savefig( fig_name )
        print("Corrwlation for all events ( freq. = " + str(chan1) + " and " + str(chan2) + " ) saved into " + fig_name )
        plt.clf()

    def corr_arg(self, chan1, chan2, fig_name = "ARG_CORR.png"):
        """Scatter plot for two complex phases"""
        datos1 = []
        datos2 = []
        for evt_fft in self.fftset:
            datos1.append( np.angle( evt_fft[chan1] ) )
            datos2.append( np.angle( evt_fft[chan2] ) )
        plt.scatter(datos1, datos2, s=10, c = "red", alpha=0.5)
        plt.grid( True )
        plt.xlabel("phase for freq. " + str(chan1))
        plt.ylabel("phase for freq. " + str(chan2))
        plt.title(r'Correlation of phases between %d and %d' %(chan1,chan2))
        plt.savefig( fig_name )
        print("Corrwlation for all events ( freq. = " + str(chan1) + " and " + str(chan2) + " ) saved into " + fig_name )
        plt.clf()

#===============================================================================
anode = anode_noise(dump_file_path)
anode.draw_event(0)
anode.draw_spectrum(0)
anode.hist_abs(17)
anode.hist_arg(17)
anode.corr_arg(16,17)
anode.corr_abs(16,17)
