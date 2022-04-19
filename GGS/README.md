# Secondaries from muons on a steel wall


## Enviorment

This project is tested with `conda` package solution.
First one have to setup and configure `conda`:
```bash
cd ~/
wget http://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh
source ~/miniconda3/etc/profile.d/conda.sh
conda config --add channels conda-forge
```

Second, create `Geant4` envoirment:
```bash
conda create --name g4-mc geant4 compilers cmake make
conda activate g4-mc
```

## Build project

```bash
mkdir build;
cd build;
cmake -DGeant4_DIR=/home/adzyuba/miniconda3/envs/g4-mc/lib/Geant4-10.7.1/ ../GGS
```
