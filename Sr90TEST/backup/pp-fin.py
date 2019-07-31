#===============================================================================
#DOSE  = 0.688456  # nanoGrey
#DOSE  = 5.320810  # nanoGrey
#DOSE  = 0.405764  # nanoGrey
DOSE  = 0.291349  # nanoGrey
N_DEC =   3750000. # simulated number of decays
N_TOT = 750000000. # source activity
cu_density = 8960  # kg/m3
r_disk     =  0.3  # 300 mm
s_disk     =  0.0115  # 23 mm dismeter mm
h_disk     =  0.035 /1000. ; # 35 um
MeV_to_pJ = 0.160217766 ;
#===============================================================================
import shelve
from math import pow, sqrt, pi, cos, sin
from random import random
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
def calc_point( d_pos , ll, N_toys = 100 ):
    res_list = []
    for tt in range(N_toys):
        phi = 2.*pi *random()
        x_pos = d_pos*cos(phi)
        y_pos = d_pos*sin(phi)
        ck = sqrt( x_pos*x_pos+y_pos*y_pos )
        toy_dose = 0.
        for w in ll:
            xx = w[0]
            yy = w[1]
            if (pow(xx-x_pos,2)+pow(xx-y_pos,2))<pow(1000.*s_disk,2) :
                toy_dose = toy_dose + w[2]
        res_list.append( toy_dose )
        if not tt%500:
            print("  toy " + str(tt) + " : " +  str(mnv(res_list)) + " pGy")
    return( mnv(res_list) )
#===============================================================================
distance = []
dose_in  = []
tl = []
in_file = open("out.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    tl.append( ( float(w[0]), float(w[1]), float(w[4])* MeV_to_pJ  / mass_disk ) )
in_file.close()
for ii in range(40):
    ddd = 1.+ii*5
    distance.append(ddd*0.1)
    dsi = calc_point(ddd,tl,3000)
    print( str(ddd) + " mm\t\t dose = " + str(dsi) + " pGy" )
    dose_in.append(dsi*0.001*0.001)
print(distance)
print(dose_in)
