# Z position measurement with ESEPP, Range and CSC

```bash
mkdir rfz
cd rfz
cmake -DGeant4_DIR=/home/geant/Sim/geant4.10.06-install/lib/Geant4-10.6.2/ ../RFZ/
pico seed1 ; source Run_Geant.sh; root -b -q fast.C+ ; root -b -q mwpc.C+
```

To analyse

```bash
root -b fast.C
python3 -m http.server 8000
```

