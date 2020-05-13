#Material and particles

A layer of material is placed in the middle of world volume.
A detector layer is placed behind of target.

Scattering angles for incoming particle as well as spectrum of secondaries
is measured by the detector layer.


```bash
mkdir new
cd new
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.06-install/lib/Geant4-10.6.0/ ../STL/
source  Run_Geant.sh
root -b analysis.C
python2 -m SimpleHTTPServer 8000
```

