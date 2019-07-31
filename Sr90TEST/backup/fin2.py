#===============================================================================
#DOSE  = 0.688456  # nanoGrey
DOSE  = 5.320810  # nanoGrey
#DOSE  = 0.405764  # nanoGrey
#DOSE  = 0.291349  # nanoGrey
N_DEC =   3750000. # simulated number of decays
N_TOT = 750000000. # source activity
cu_density = 8960  # kg/m3
r_disk     =  0.3  # 300 mm
s_disk     =  0.0115  # 23 mm dismeter mm
h_disk     =  0.035 /1000. ; # 35 um
MeV_to_pJ = 0.160217766 ;
#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi, cos, sin
from random import random
from scipy.optimize import curve_fit
#===============================================================================
mass_disk  = cu_density * pi *pow( s_disk,2)*h_disk
to_pGy     = MeV_to_pJ  / mass_disk
per_second = N_TOT / N_DEC
to_pGy_per_second = to_pGy * per_second
#===============================================================================
def mnv(ll):
    sl = 0.
    cntr = 0.
    for itm in ll:
        cntr = cntr + 1.
        sl = sl + itm
    return sl/cntr
#===============================================================================
def calc_point( d_pos , N_toys = 100 ):
    #print("START POINT : " + str(d_pos) + " mm \t(" + str(N_toys) + " toys)")
    res_list = []
    for tt in range(N_toys):
        phi = 2.*pi *random()
        x_pos = d_pos*cos(phi)
        y_pos = d_pos*sin(phi)
        ck = sqrt( x_pos*x_pos+y_pos*y_pos )
        in_file = open("out.data","r")
        toy_dose = 0.
        for line in in_file:
            w = line[:-1].split(" ")
            xx = float( w[0] )
            yy = float( w[1] )
            if (pow(xx-x_pos,2)+pow(xx-y_pos,2))<pow(1000.*s_disk,2) :
                toy_dose = toy_dose + float( w[4] )
        in_file.close()
        #print( str(ck) + "\t" + str(toy_dose* MeV_to_pJ  / mass_disk) + " pGy")
        res_list.append( toy_dose* MeV_to_pJ  / mass_disk )
        if not tt%500:
            print("  toy " + str(tt) + " : " +  str(mnv(res_list)) + " pGy")
    #print(" ---> DONE")
    return( mnv(res_list) )
#===============================================================================
distance = []
dose_in  = []
for ii in range(40):
    ddd = 1.+ii*5
    distance.append(ddd*0.1)
    dsi = calc_point(ddd,3000)
    print( str(ddd) + " mm\t\t dose = " + str(dsi) + " pGy" )
    dose_in.append(dsi*0.001*0.001)
print(dose_in)
#===============================================================================
plt.plot(distance, dose_in)
plt.xlabel('Distance, cm')
plt.ylabel('Dose, microGy / s')
#plt.title('Do')
#plt.axis([0.,3,0.000001,1])
plt.grid(True)
plt.yscale('log')
plt.savefig("TEMP2.png")
print(distance)
print(dose_in)
