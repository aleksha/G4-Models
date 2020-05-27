#!/bin/bash
rm *LOG;
source /home/user/Sim/geant4.10.06-install/bin/geant4.sh;
make;
./exec_POS run.mac >> inLOG;
