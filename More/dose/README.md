# dose

Small GEANT-4 project to calculate dose distribution in the wall of the multi wire chamber.

See report about results in **_MC4DOSE.docx_** file.

In **_HOW-TO-RUN.md_** one can find information about software stack, installation and
running things inside cloud infrastructure.

About model 
-----------

Repository contains different GEANT-4 **Sr99TEST** model, developed for tests 
of radiational damage of MWPC for CMS with the Sr-99 beta source.
Code uses **_SteppingAction_** class to get detector response.

To build and run executable
---------------------------

```bash
mkdir build ;  cd build ;
cmake -DGeant4_DIR=/home/user/Sim/geant4.10.04.p02-install/lib/Geant4-10.4.2/ ../Sr90TEST ;
```

To compile and run with the **_run.mac_** macro:
```bash
source Run_Geant.sh ;
```
Logs will be in **_inLOG_** file.

