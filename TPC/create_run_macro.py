#===============================================================================
# this python macro creates RUN file
#===============================================================================

f_in   = open("CONFIG.txt","r")
f_out1 = open("myRUNin.mac"    ,"w")
f_out2 = open("myRUNout.mac"   ,"w")
f_out3 = open("myRUNpileup.mac","w")

energy = 100.0
n_ev = 1
for line in f_in:
    w = line.split(" ")
    if w[0] == "Number_of_events" : n_ev    = int(w[1])
    if w[0] == "Electron_energy"  : energy  = float(w[1])
    if w[0] == "zTPC"             : zTPC    = float(w[1])
    if w[0] == "MatMode"          : MatMode = float(w[1])


b1 = "/control/verbose 0\n/tracking/verbose 0\n"
b2 = "/event/verbose 0\n/run/verbose 0\n/run/initialize\n"

b_rnd1 = "/random/resetEngineFrom seed1\n"
b_rnd2 = "/random/resetEngineFrom seed2\n"
b_rnd3 = "/random/resetEngineFrom seed3\n"

b = b1+b2

f_out1.write(b + b_rnd1)
f_out2.write(b + b_rnd2)
f_out3.write(b + b_rnd3)

f_out1.write("/run/beamOn " + str(n_ev) + "\n")
f_out2.write("/run/beamOn " + str(n_ev) + "\n")
f_out3.write("/run/beamOn " + str(200*n_ev) + "\n")

f_in.close()
f_out1.close()
f_out2.close()
f_out3.close()
