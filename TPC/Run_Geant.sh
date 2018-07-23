#!/bin/bash
rm *LOG;
source /home/user/Sim/geant4.10.04.p02-install/bin/geant4.sh;
make;
echo "Creating myRUN.mac";
python create_run_macro.py;
python create_in_config.py;
echo "Start GEANT4 for initial distribution"
./exec_TPC run.mac >> inLOG;
