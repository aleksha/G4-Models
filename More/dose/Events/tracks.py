#===============================================================================
axis = "x"
#num =  32331
#num =  61763
#num =  69920
num =  109076
#num = 311656
#num = 489784
#===============================================================================
import shelve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.lines  as lines
import matplotlib.pyplot as plt
import matplotlib.mlab   as mlab
from math import pow, sqrt, pi, fabs
from matplotlib.pyplot import figure
#===============================================================================
fig, ax = plt.subplots()
plt.axis([-350,  350, -350,  350])
plt.grid(True)
if axis=="x":
    plt.xlabel('x, mm')
else :
    plt.xlabel('y, mm')
plt.ylabel('z, mm')
fig.set_size_inches(6,6)
#===============================================================================
r_Sr = plt.Rectangle( ( -16,-36  ),  32, 36 , fc="y")
plt.gca().add_patch( r_Sr )
r_A1 = plt.Rectangle( (-300,  1.5), 600, 10 , fc="y")
plt.gca().add_patch( r_A1 )
r_A2 = plt.Rectangle( (-300, 21.5), 600, 10 , fc="y")
plt.gca().add_patch( r_A2 )
r_Ar = plt.Rectangle( (-300, 13.0), 600,  9 , fc="y")
plt.gca().add_patch( r_Ar )
#===============================================================================
y0 = [] ; z0 = [] ; in_file = open("dump.data","r")
for line in in_file:
    w = line[:-1].split(" ")
    if int(w[0]) == num:
        if int(w[1]) == 11:
            cl = "red"
        else :
            cl = "blue"
        xs = float(w[2]); ys = float(w[3]); zs = float(w[4])
        xe = float(w[5]); ye = float(w[6]); ze = float(w[7])
        if axis == "x":
            ax.add_line( lines.Line2D( [xs,xe], [zs,ze] ,linewidth=3, color = cl ) )
        else:
            ax.add_line( lines.Line2D( [ys,ye], [zs,ze] ,linewidth=3, color = cl ) )
in_file.close()
#===============================================================================
plt.scatter(y0,z0, s=1, c = "black" , alpha=0.5, lw=0) # Cu layer 2
plt.title('EVENT ' + str(num) )
#plt.yscale('log')
plt.savefig("TEMP.png")
#===============================================================================
