#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi, fabs
#===============================================================================
from matplotlib.pyplot import figure
figure(num=None, figsize=(6, 6), dpi=100, facecolor='w', edgecolor='w')
#===============================================================================
y0 = [] ; z0 = [] ; in_file = open("g_cu2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y0.append(float(w[1])) ; z0.append(float(w[2]))
in_file.close()
#===============================================================================
y1 = [] ; z1 = [] ; in_file = open("g_Sr.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y1.append(float(w[1])) ; z1.append(float(w[2]))
in_file.close()
#===============================================================================
y2 = [] ; z2 = [] ; in_file = open("g_Ar.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y2.append(float(w[1])) ; z2.append(float(w[2]))
in_file.close()
#===============================================================================
y3 = [] ; z3 = [] ; in_file = open("g_air2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y3.append(float(w[1])) ; z3.append(float(w[2]))
in_file.close()
#===============================================================================
y4 = [] ; z4 = [] ; in_file = open("g_air1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y4.append(float(w[1])) ; z4.append(float(w[2]))
in_file.close()
#===============================================================================
y5 = [] ; z5 = [] ; in_file = open("g_steel1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    if fabs( float(w[1]) ) > 1 :
        y5.append(float(w[1])) ; z5.append(float(w[2]))
in_file.close()
#===============================================================================
y6 = [] ; z6 = [] ; in_file = open("g_steel2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y6.append(float(w[1])) ; z6.append(float(w[2]))
in_file.close()
#===============================================================================
y7 = [] ; z7 = [] ; in_file = open("plexi1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    if fabs( float(w[1]) ) > 3 :
        y7.append(float(w[1])) ; z7.append(float(w[2]))
in_file.close()
#===============================================================================
y8 = [] ; z8 = [] ; in_file = open("plexi2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    y8.append(float(w[1])) ; z8.append(float(w[2]))
in_file.close()
#===============================================================================
y9 = [] ; z9 = [] ; in_file = open("pb1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    if fabs( float(w[1]) ) > 8 :
        y9.append(float(w[1])) ; z9.append(float(w[2]))
in_file.close()
#===============================================================================
yq = [] ; zq = [] ; in_file = open("pb2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yq.append(float(w[1])) ; zq.append(float(w[2]))
in_file.close()
#===============================================================================
yw = [] ; zw = [] ; in_file = open("gt1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yw.append(float(w[1])) ; zw.append(float(w[2]))
in_file.close()
#===============================================================================
ye = [] ; ze = [] ; in_file = open("gt2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    ye.append(float(w[1])) ; ze.append(float(w[2]))
in_file.close()
#==============================r=================================================
yr = [] ; zr = [] ; in_file = open("gt3.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yr.append(float(w[1])) ; zr.append(float(w[2]))
in_file.close()
#===============================================================================
yt = [] ; zt = [] ; in_file = open("gt4.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yt.append(float(w[1])) ; zt.append(float(w[2]))
in_file.close()
#===============================================================================
ya = [] ; za = [] ; in_file = open("cu1.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    ya.append(float(w[1])) ; za.append(float(w[2]))
in_file.close()
#===============================================================================
ys = [] ; zs = [] ; in_file = open("cu2.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    ys.append(float(w[1])) ; zs.append(float(w[2]))
in_file.close()
#===============================================================================
yd = [] ; zd = [] ; in_file = open("cu3.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yd.append(float(w[1])) ; zd.append(float(w[2]))
in_file.close()
#===============================================================================
yf = [] ; zf = [] ; in_file = open("cu4.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    yf.append(float(w[1])) ; zf.append(float(w[2]))
in_file.close()
#===============================================================================
plt.scatter(y0,z0, s=1, c = "black" , alpha=0.5, lw=0) # Cu layer 2
plt.scatter(y2,z2, s=1, c = "red"   , alpha=0.5, lw=0) # Ar gas
plt.scatter(y1,z1, s=1, c = "black" , alpha=0.5, lw=0) # Source
plt.scatter(y3,z3, s=1, c = "blue"  , alpha=0.5, lw=0)
plt.scatter(y4,z4, s=1, c = "blue"  , alpha=0.5, lw=0)
plt.scatter(y5,z5, s=1, c = "green" , alpha=0.5, lw=0)
plt.scatter(y6,z6, s=1, c = "green" , alpha=0.5, lw=0)
plt.scatter(y7,z7, s=1, c = "gray"  , alpha=0.5, lw=0)
plt.scatter(y8,z8, s=1, c = "gray"  , alpha=0.5, lw=0)
plt.scatter(y9,z9, s=1, c = "brown" , alpha=0.5, lw=0)
plt.scatter(yq,zq, s=1, c = "brown" , alpha=0.5, lw=0)
plt.scatter(yw,zw, s=1, c = "yellow", alpha=0.5, lw=0)
plt.scatter(ye,ze, s=1, c = "yellow", alpha=0.5, lw=0)
plt.scatter(yr,zr, s=1, c = "yellow", alpha=0.5, lw=0)
plt.scatter(yt,zt, s=1, c = "yellow", alpha=0.5, lw=0)
plt.scatter(ya,za, s=1, c = "black", alpha=0.5, lw=0)
plt.scatter(ys,zs, s=1, c = "black", alpha=0.5, lw=0)
plt.scatter(yd,zd, s=1, c = "black", alpha=0.5, lw=0)
plt.scatter(yf,zf, s=1, c = "black", alpha=0.5, lw=0)
plt.xlabel('y, mm')
plt.ylabel('z, mm')
#plt.title('Do')
plt.axis([-40,  40, -40,  40])
plt.grid(True)
#plt.yscale('log')
plt.savefig("TEMP.png")
#===============================================================================
