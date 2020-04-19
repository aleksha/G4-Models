# Notes on How-to-Run

Software stack can be used on servers provided by clouds.
Existing software stack has been tested with https://vscale.io
infrustructure with the 400 RUB/month instance 
(1 Gb RAM / 30 Gb SSD / 1 CPU).

Software stack:
 * Ubuntu 16.04 LTS,
 * ROOT 5.34.38 (1 hour to compile),
 * Geant 4.10.4 (1.5 hours to compile),
 * Python 2.9 (with numpy, scipy and matplotlib).

To access commad line:
 * **Linux** -- use any terminal
 * **Windows** -- http://cmder.net/
 * **macOS** -- https://www.iterm2.com/ (not tested)
 
Using cloud infrastructure
==========================

Instread of using virtual machines, which share limitations of the existing PCs 
and have some difficulties with installation of the operation systems,
a cloud solution is proposed.

Next provider are tested:
  * https://vscale.io (Russian provider, used as default one [English mode])
  * https://digitalocean.com (had some difficulties with connetion to Russia)
  
**Note:** the opportunity to use other ways as locally installed software,
virtual machines and so on is not forbidden, but will have no support.

Create RSA key pair for SSH conection
--------------------------------------

(one can read https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/)
 
Mainly:

```bash
cd ~/.ssh/
ssh-keygen 
```

It's safer to add passphrase, but you will have to type it everytime...

To read publich key:
```bash
cat ~/.ssh/id_rsa.pub
```

Setup server at vscale enviorement:
-----------------------------------

 1. Create an account and put some payment (200 RUB will cover half a month usage)
 
 2. Servers -> Create Server:  Choose
   * Ubuntu 16.04 64bit
   * 400 RUB/month server
   * Saint-Petersburg location (for PNPI)
   * Server name (name of server at the pannel)
   * Host name (name of server on server)
   * upload SSH public key
   * Create Server
   
 3. After server will have status _Online_ use ssh to login
 
```bash
ssh -i/.ssh/id_rsa root@IP_ADDRESS
```

 4. Update software, create user, switch to it
```bash
apt update
apt upgrade
useradd -m user
passwd user
adduser user sudo
su user
```

Software installation
=====================

 1. Install (gat root access to) Xubuntu 16.04 LTS

 2. Update software
 
```bash
sudo apt-get update
sudo apt-get upgrade
```

 3. CERN ROOT installtion

  3.1 Download ROOT from https://root.cern.ch/content/release-53436
  
  3.2 Install packages
  
```bash
sudo apt-get install git dpkg-dev cmake g++ gcc binutils \ 
  libx11-dev libxpm-dev libxft-dev libxext-dev
sudo apt-get install gfortran libssl-dev libpcre3-dev \
  xlibmesa-glu-dev libglew1.5-dev libftgl-dev libmysqlclient-dev \
  libfftw3-dev libcfitsio-dev graphviz-dev libavahi-compat-libdnssd-dev \
  libldap2-dev python-dev libxml2-dev libkrb5-dev libgsl0-dev libqt4-dev
```

  3.3 Compile ROOT

```bash
sudo cp root_v5.34.36.source.tar.gz /usr/local/
cd /usr/local/
sudo tar zxvf root_v5.34.36.source.tar.gz
cd root/
sudo ./configure
sudo make
```

  3.4 Add next ROOT paths to **_~/.bashrc_**
```bash
export ROOTSYS=/usr/local/root
export PATH=$ROOTSYS/bin:/usr/local/bin:./$PATH
export LD_LIBRARY_PATH=$ROOTSYS/lib:/usr/lib/mysql:$LD_LIBRARY_PATH
```

 4. GEANT4 installation

  4.1 Download GEANT4 to local machine http://geant4.web.cern.ch/geant4/support/download.shtml
 
  **at local machine**
```bash
scp -i ..\.ssh\YOURKEY geant4.10.04.p02.tar.gz root@IPADRESS:/home/user/Sim/
```
    
  4.2 Stack of commands

```bash
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libmotif-dev
cd ~/Sim/
tar zxvf geant4.10.04.p02.tar.gz
mkdir ~/Sim/geant4.10.04.p02-build
cd ~/Sim/geant4.10.04.p02-build
cmake -DCMAKE_INSTALL_PREFIX=/home/user/Sim/geant4.10.04.p02-install /home/user/Sim/geant4.10.04.p02
cmake -DGEANT4_INSTALL_DATA=ON .
make
make install
```

5. Python packages installation

```bash
sudo apt-get install python-numpy python-scipy python-matplotlib \
  ipython ipython-notebook python-pandas python-sympy python-nose
```
