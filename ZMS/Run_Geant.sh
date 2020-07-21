#!/bin/bash
rm *LOG;
source /home/geant/Sim/geant4.10.06-install/bin/geant4.sh;
make;
./exec_ZMS run.mac >> inLOG;
