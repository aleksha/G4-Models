# G4-Models

Models for GEANT-4

Repository contains different GEANT-4 models, which use 
**_SteppingAction_** class to get detector response. These are:
 + **PROTON** - big TPC equiped with MWPC\CSC;
 + **CSC** - prototipe of the CSC;
 + **ACTAF** - TPC prototype;
 + **Sr99TEST** - test of radiational damage of MWPC for CMS
    with the Sr-99 beta source.

To build executable (for example for Sr90TEST project)
------------------------------------------------------

```bash
mkdir build ;  cd build ;
```

Type 
```bash
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.04.p02-install/lib/Geant4-10.4.2/ ../Sr90TEST ;
```
or
```bash
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.04.p02-install/lib/Geant4-10.4.2/ ../CSC ;
```

To compile and run with the **_run.mac_** macro:
```bash
source Run_Geant.sh ;
```
Logs will be in **_inLOG_** file.
