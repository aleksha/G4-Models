# Z position measurement


```bash
mkdir zms
cd zms
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.06-install/lib/Geant4-10.6.0/ ../ZMS/
source  Run_Geant.sh
```

To analyse

```bash
root -b analyse.C
python3 -m http.server 8000
```

