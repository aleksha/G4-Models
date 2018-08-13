#===============================================================================
# see for details
# https://docs.scipy.org/doc/scipy/reference/generated/scipy.fftpack.rfft.html#scipy.fftpack.rfft
#===============================================================================
#dump_file_path = "./dump.txt"
dump_file_path = "/home/user/Temp/dump.txt"
N_CHANNELS     = 2692
#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from   scipy.fftpack import  fft,  ifft
from   scipy.fftpack import rfft, irfft
from   scipy.stats   import norm, chi2
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
        self.channels = N_CHANNELS
        self.events   = 0
        print("Loading anode dump file")
        self.path = dump_path
        self.dataset = []
        dumpfile = open(self.path,"r")
        for line in dumpfile:
            value_str_list = (line[:-1]).split(",")
            value_list = []
            for idx in range(self.channels):
                value_list.append( float( value_str_list[idx] ) )
            self.dataset .append( np.array( value_list ) )
            self.events   = self.events + 1
        dumpfile.close()
        print("CHANNELS : " + str( self.channels ) )
        print("EVENTS   : " + str( self.events   ) )
        fft_list  = []
        fft_list2 = []
        print("Performing fast Fourier transformation")
        for event in self.dataset:
            fft_list .append(  fft( event ) )
        self.fftset  = fft_list

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

    def draw_extended_event(self, num, fig_name = "EXTD_EVENT.png"):
        """Draw event number num into figure fig_name"""
        evt_fft = np.copy ( self.fftset[num] )
        evt_newl = []

        for ii in range(0,self.channels):
            evt_newl.append( evt_fft[ii]*2. )
            evt_newl.append( 0 )

        evt_new = np.array(evt_newl)
        ext_event  = ifft( evt_new )

        plt.plot( ext_event, "r" )
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
        print(" len ( freq ) = " + str( len( self.fftset[0] ) ) )
        plt.clf()

    def draw_average_spectrum(self, fmin = 1, fmax = 100,  fig_name = "SPECTRUM_AVE.png"):
        """Draw absolute value of frequiency spectrum"""

        means = []
        for chan in range(fmin,fmax):
            datos = []
            for evt_fft in self.fftset :
                datos.append( np.abs( evt_fft[chan] ) )
            (mu, sigma) = norm.fit(datos)
            means.append( mu/self.channels )
        plt.plot( means )
        plt.grid( True )
        plt.xlabel("freq., 1/num.of.ch.")
        plt.ylabel("mean abs. val., a.u.")
        plt.title('Average spectrum')
        plt.savefig( fig_name )
        print("Distribution of absolute value to " + fig_name )
        print("  in range = ("+str(fmin) + ","+str(fmax) + ")")
        plt.clf()

    def hist_abs(self, chan, fig_name = "ABS_VAL.png"):
        """Distribution of abs. val. for frequency channel for all events"""
        datos = []
        for evt_fft in self.fftset:
            datos.append( np.abs( evt_fft[chan] )/self.channels )
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
        n, bins, patches = plt.hist(datos, self.events/100, facecolor='green')
        plt.grid( True )
        plt.xlabel("complex phase")
        plt.ylabel("events")
        plt.title(r'Distribution for FREQ %d' %(chan))
        plt.savefig( fig_name )
        print("Distribution of compex phase for all events ( freq. = " + str(chan) + " ) saved into " + fig_name )
        plt.clf()

    def check_args(self, chi2_alpha = 0.997, fig_name = "CHCK_ARGS.png"):
        """Make chi2 test that argument distributions are flat"""
        print("\n\n====== CHECK THAT PHASE IS FLAT ======\n")
        for chan in range(1,self.channels/2):
            datos = []
            for evt_fft in self.fftset:
                datos.append( np.angle( evt_fft[chan] ) )
            n, bins, patches = plt.hist(datos, self.events/100, facecolor='green')
            chi2_obs = 0.
            for n_i in n:
                chi2_obs = chi2_obs + float( pow( n_i-100 ,2) )/float(n_i)
            if chi2_obs > chi2.interval(chi2_alpha,len(n))[1]:
                print("-----> CHANNEL " + str(chan) + "\t OBS. :" + str(chi2_obs) + "\t EXP.: " + str(chi2.interval(chi2_alpha,len(n)) ) )
            elif chi2_obs < chi2.interval(chi2_alpha,len(n))[0]:
                print("-----> CHANNEL " + str(chan) + "\t OBS. :" + str(chi2_obs) + "\t TOO GOOD TO BE TRUE" )
            else:
                print("-----> CHANNEL " + str(chan) + "\t OBS. :" + str(chi2_obs) + "\t FINE" )
            plt.clf()
        print("\n======      END PHASE CHECK     ======\n")

    def check_args_corr(self, chan_min   = 0 , chan_stop=256, chan_max = 256,
                              chan_depth = 10, chan2_shift = 0,
                              chi2_alpha = 0.997, fig_name = "CHCK_DIFF.png"):
        """Make chi2 test that chan1 chan2 argument difference distributions are flat"""
        print("\n\n====== CHECK THAT DIFF. IS FLAT ======\n")

        rdb = shelve.open("temp_store.shelve")
        tmp_arr_2d = rdb["phase_diff_array"]

        if len(tmp_arr_2d)<chan_max:
            arr_2d = np.zeros( (chan_max,chan_max) )
            for ch1 in range(0,chan_max):
                for ch2 in range(0,chan_max):
                    arr_2d[ch1][ch2] = 0.5
            for ch1 in range(len(tmp_arr_2d)):
                for ch2 in range(0,len(tmp_arr_2d)):
                    arr_2d[ch1][ch2] = tmp_arr_2d[ch1][ch2]
        else:
            arr_2d = tmp_arr_2d

        for chan1 in range(chan_min,chan_stop):
            print("-----> CHANNEL " + str(chan1) + " / " + str(chan_stop) )
            for chan2 in range(chan1+chan2_shift,chan1+chan2_shift+chan_depth):
                if chan2 < chan_max and chan1<chan_max:
                    if arr_2d[chan1][chan2]>0. or arr_2d[chan1][chan2]<1.:
                        datos = []
                        for evt_fft in self.fftset:
                            if np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) > 0 :
                                datos.append( np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) )
                            else :
                                datos.append( np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) + pi*2. )
                        n, bins, patches = plt.hist(datos, self.events/100, facecolor='green')
                        plt.title(r'Difference of phases between %d and %d' %(chan1,chan2))
                        plt.savefig("TEMP.png")
                        if chan1 == chan2 :
                            arr_2d[chan1][chan2]=0.
                        else:
                            chi2_obs = 0.
                            for n_i in n:
                                chi2_obs = chi2_obs + float( pow( n_i-100 ,2) )/float(n_i)
                            if chi2_obs > chi2.interval(chi2_alpha,len(n))[1]:
                                arr_2d[chan1][chan2]=1.
                            else:
                                arr_2d[chan1][chan2]=0.
                        plt.clf()

        for ch1 in range(0,chan_max):
            for ch2 in range(ch1+1,chan_max):
                arr_2d[ch2][ch1] = arr_2d[ch1][ch2]

        plt.imshow(arr_2d,cmap="gray", interpolation='none')
        plt.tight_layout()
        plt.xlabel("channel")
        plt.ylabel("channel")
        plt.title(r'Non-flat phases difference between channels')
        plt.savefig(fig_name)
        plt.clf()
        print("\n======      END DIFF. CHECK     ======\n")
        rdb.close()
        return arr_2d

    def corr_scatter(self, chan1, chan2, fig_name = "CORR_SCT.png"):
        """Scatter plot for two channels"""
        datos1 = []
        datos2 = []
        datos3 = []
        datos4 = []
        for evt_fft in self.fftset:
            datos1.append( np.real( evt_fft[chan1] ) )
            datos2.append( np.imag( evt_fft[chan1] ) )
            datos3.append( np.real( evt_fft[chan2] ) )
            datos4.append( np.imag( evt_fft[chan2] ) )
        plt.scatter(datos1, datos2, s=1, c = "red" , alpha=0.5)
        plt.scatter(datos3, datos4, s=1, c = "blue", alpha=0.5)
        plt.grid( True )
        plt.savefig( fig_name )
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

    def phase_abs(self, chan1,fig_name = "ABS_ARG.png"):
        """Scatter plot for abs and complex phases"""
        datos1 = []
        datos2 = []
        for evt_fft in self.fftset:
            datos1.append( np.angle( evt_fft[chan1] ) )
            datos2.append( np.abs  ( evt_fft[chan1] ) )
        plt.scatter(datos1, datos2, s=10, c = "green", alpha=0.5)
        plt.grid( True )
        plt.savefig( fig_name )
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

    def diff_arg(self, chan1, chan2, fig_name = "ARG_DIFF.png"):
        """Diggerence for two complex phases"""
        datos = []
        for evt_fft in self.fftset:
            if np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) > 0 :
                datos.append( np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) )
            else :
                datos.append( np.angle( evt_fft[chan1] ) - np.angle( evt_fft[chan2] ) + pi*2. )
        n, bins, patches = plt.hist(datos, 30, facecolor='red', alpha = 0.75)
        plt.grid( True )
        plt.xlabel("phase " + str(chan1) + " - phase " + str(chan2))
        plt.ylabel("events")
        plt.title(r'Difference of phases between %d and %d' %(chan1,chan2))
        plt.savefig( fig_name )
        print("Difference for all events ( freq. = " + str(chan1) + " and " + str(chan2) + " ) saved into " + fig_name )
        plt.clf()

#===============================================================================
anode = anode_noise(dump_file_path)

#anode.draw_event(20)
#anode.draw_extended_event(20)
#anode.draw_spectrum(20)
#anode.draw_average_spectrum(1,200)
#anode.hist_abs(100)
#anode.hist_arg(100)
#anode.phase_abs(100)
#anode.diff_arg(100,150)
#anode.corr_arg(100,150)
#anode.corr_abs(100,150)
anode.corr_scatter(100,100)

#anode.check_args()

#a2d = anode.check_args_corr(chan_min = 0, chan_stop = 50, chan_max = 300, chan_depth = 100, chan2_shift = 50)
#rdb = shelve.open("temp_store.shelve")
#rdb["phase_diff_array"] = a2d
#rdb.close()
