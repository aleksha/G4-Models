#Detemine drift velocity resolution


```bash
mkdir build
cd build
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.06-install/lib/Geant4-10.6.0/ ../POS/
source  Run_Geant.sh
root -b ionization.C
python3 -m http.server 8000
```

## Model (layers)

 1. Silicon traker (entrance) --> **out.data**
 2. Scintillator layer (entrance)  --> **out.data**
 3. Beryllium entrance-window
 4. Hydrogen layer --> **out.data**
 5. Beryllium exit-window
 6. Silicon tracker (exit)  --> **out.data**
 7. Scintillator layer (exit) --> **out.data**

