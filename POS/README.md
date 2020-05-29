#Detemine drift velocity resolution


```bash
mkdir build
cd build
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.06-install/lib/Geant4-10.6.0/ ../POS/
source  Run_Geant.sh
root -b ionization.C
python3 -m http.server 8000
```
This will reurn **TEMP.png** with energy deposite in Scintillators and in Hydroden.

To fe FlashADC spectrum, run **fadc.py**. Parameters are:
  1. Measurement position in mm from anode plane;
  2. Number of events to accumulate.

```bash
root -b "fadc.C(10.,10000)" ; python3 -m http.server 8000
root -b estimators.C+ ; python3 -m http.server 8000
```

## Signal processing

In previous version a signal apears, when an electron reach the anode.
On practice a current starts, when an electron reach the grid.
The current is linearly rising during a drift between grid and anode.
An integral of this current is equal to the charge of one electron.
A new procedure is done in **conv.C**. The result is stored
in the **Digi.txt** file, which have to be loaded.

```bash
root -b conv.C
```

## Longitudinal diffusion

**sigma_Z = 0.008*sqrt(L)**

**L** ans **sigma_Z**  in cm.

```bash
root -b diffusion.C+
```


## Model (layers)

 1. Silicon traker (entrance) --> **out.data**
 2. Scintillator layer (entrance)  --> **out.data**
 3. Beryllium entrance-window
 4. Hydrogen layer --> **out.data**
 5. Beryllium exit-window
 6. Silicon tracker (exit)  --> **out.data**
 7. Scintillator layer (exit) --> **out.data**

