#!/bin/bash
rm *LOG;
root -l -b create_pdf.C;
source /home/user/Sim/geant4.10.04.p02-install/bin/geant4.sh;
make;
./exec_Sr90TEST run.mac >> inLOG;
