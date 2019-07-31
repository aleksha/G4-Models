#===============================================================================
DOSE  = 0.688456  # nanoGrey
#DOSE  = 5.320810  # nanoGrey
#DOSE  = 0.405764  # nanoGrey
#DOSE  = 0.291349  # nanoGrey
N_DEC =   3750000. # simulated number of decays
N_TOT = 750000000. # source activity
cu_density = 8960  # kg/m3
r_disk     =  0.3  # 300 mm
h_disk     =  0.035 /1000. ; # 35 um
MeV_to_pJ = 0.160217766 ;
#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi
from scipy.optimize import curve_fit
#===============================================================================
def dose_density(x, D, frac, sigma, k, b):
    return D*( ( frac*np.exp( - 0.5*x*x/sigma/sigma ) /(sigma*np.sqrt(2.*pi)) ) + ( (1.-frac)*(b*np.exp(-k*x))) )
#    return D*( ( frac*np.exp( - 0.5*x*x/sigma/sigma ) /(sigma*np.sqrt(2.*pi)) ) + ( (1.-frac)*(b +k*x) ) )
#===============================================================================
mass_disk  = cu_density * pi *pow( r_disk,2)*h_disk
to_pGy     = MeV_to_pJ  / mass_disk
per_second = N_TOT / N_DEC
to_pGy_per_second = to_pGy * per_second
#===============================================================================
in_file = open("out.data","r")
sum_w = 0. ; sum_in =0.; sum_out = 0;
for line in in_file:
    w = line[:-1].split(" ")
    if float(w[3])<300 :
        sum_w = sum_w + float( w[4])
        if float(w[3])<12.5 :
            sum_in  = sum_in  + float( w[4] )
        else :
            sum_out = sum_out + float( w[4] )
in_file.close()
#===============================================================================
print("REPORTED DOSE   : " + str( DOSE                           ) + " nGy"   )
print("  ----> chack   : " + str( sum_w * MeV_to_pJ  / mass_disk ) + " pGy"   )
print("         mass   : " + str( mass_disk*1000.                ) + " gr"    )
print("       energy   : " + str( sum_w                          ) + " MeV"   )
print("       energy   : " + str( sum_w * MeV_to_pJ              ) + " pJ"    )
print("CALCULATED DOSE : " + str( DOSE   * N_TOT / N_DEC         )            )
print("sum_w           : " + str( sum_w  * N_TOT / N_DEC         )            )
print("fraction lost   : " + str( 100.* sum_out / (sum_in + sum_out) )  + " %")
#===============================================================================
dist    = []
weights = []
doses   = []
in_file = open("out.data","r")
for line in in_file:
    w = line[:-1].split(" ")
#    if float(w[3])<300 and float(w[3])>30 :
    if float(w[3])<300 :
        dist   .append( float(w[3]) )
#        weights.append( 20. )
        weights.append( float(w[4]) * DOSE * N_TOT / sum_w / N_DEC )
        doses  .append( float(w[4]) * to_pGy_per_second )
#        weights.append( 1./(2.*pi*float(w[3])) )
#        weights.append( float(w[4]) / (2.*pi*float(w[3])) )
in_file.close()
#===============================================================================
bins = []
for ii in range(301):
    bins.append(ii)
#===============================================================================
n, bins, patches = plt.hist( x       = np.array( dist  ) ,
                             weights = np.array( doses ) ,
                             bins    = bins    ,
                             facecolor='red', alpha=0.75)
#===============================================================================
#print( n    )
#print( bins )
#===============================================================================
new_n = []
new_bins = []
short_bins = []
short_n = []
for idx in range(len(n)):
    new_bins.append( 0.1*idx )
#    new_n.append( 100*0.001*0.001*2.5*30*24*3600*0.001*n[idx] / ( pi * ( 1.+2.*idx ) ) )
    new_n.append( 0.001*n[idx] *100 / ( pi * ( 1.+2.*idx ) ) )
    if 0.1*idx<12:
        short_bins.append( 0.1*idx )
        short_n.append( 0.001*n[idx] *100 / ( pi * ( 1.+2.*idx ) ) )
#===============================================================================
#print( new_n    )
#print( bins )
#===============================================================================
plt.clf()
#plt.plot(new_bins, new_n)
plt.plot(short_bins, short_n)
popt, pcov = curve_fit(dose_density, short_bins, short_n)
print(popt)
print("\n\n\n")
print(pcov)
xdata = np.array( short_bins )
plt.plot(xdata, dose_density(xdata, *popt), 'g--' )
#===============================================================================
plt.xlabel('Distance, cm')
plt.ylabel('Dose, pGy / (s * cm2)')
#plt.title('Do')
#plt.axis([0.,3,0.000001,1])
plt.grid(True)
plt.yscale('log')
plt.savefig("DOSE.png")
#===============================================================================
