#===============================================================================
# this python macro creates CONFIG file
#===============================================================================

f_in   = open("CONFIG.txt","r")
f_out  = open("genCONFIG.txt","w")

for line in f_in:
    if line[0]!="#":
        w = line.split(" ")
        if w[0] == "Number_of_events" : n_ev         = float(w[1])
        if w[0] == "Electron_energy"  : energy       = float(w[1])
        if w[0] == "Tp"               : Tp           = float(w[1])
        if w[0] == "zTPC"             : zTPC         = float(w[1])
        if w[0] == "MatMode"          : MatMode      = float(w[1])
        if w[0] == "lTPC"             : lTPC         = float(w[1])
        if w[0] == "BeWindow"         : BeWindow     = float(w[1])
        if w[0] == "Ar1"              : Ar1          = float(w[1])
        if w[0] == "Ar2"              : Ar2          = float(w[1])
        if w[0] == "MWPCgap"          : MWPCgap      = float(w[1])
        if w[0] == "BeamSmearing"     : BeamSmearing = float(w[1])
        if w[0] == "BeamTheta"        : BeamTheta    = float(w[1])
        if w[0] == "BeamPos"          : BeamPos      = float(w[1])
        if w[0] == "TrackProtons"     : TrackProtons = float(w[1])
        if w[0] == "UseMuons"         : UseMuons     = float(w[1])
        
f_out.write( "0 " + str(n_ev)         + "\n")
f_out.write( "1 " + str(energy)       + "\n")
f_out.write( "2 " + str(zTPC)         + "\n")
f_out.write( "3 " + str(Tp)           + "\n")
f_out.write( "4 0.0\n"                      )
f_out.write( "5 " + str(MatMode)      + "\n")
f_out.write( "6 " + str(lTPC)         + "\n")
f_out.write( "7 " + str(BeWindow)     + "\n")
f_out.write( "8 " + str(Ar1)          + "\n")
f_out.write( "9 " + str(Ar2)          + "\n")
f_out.write("10 " + str(MWPCgap)      + "\n")
f_out.write("11 " + str(BeamSmearing) + "\n")
f_out.write("12 " + str(BeamTheta)    + "\n")
f_out.write("13 " + str(BeamPos)      + "\n")
f_out.write("14 " + str(TrackProtons) + "\n")
f_out.write("15 " + str(UseMuons)     + "\n")

f_in.close()
f_out.close()

