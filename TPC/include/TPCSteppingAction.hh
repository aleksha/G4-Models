#ifndef TPCSteppingAction_h
#define TPCSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct sa_Config {
  int    N_ev         ;
  double E_e          ;
  double Tp           ;
  double Pressure     ;
  double zTPC         ;
  double lTPC         ;
  int    MatMode      ;
  int    BeWindow     ;
  int    BeamSmearing ;
  double BeamTheta    ;
  double BeamPos      ;
};



class TPCEventAction;
class G4LogicalVolume;

/// Stepping action class
///

class TPCSteppingAction : public G4UserSteppingAction
{
  public:
    TPCSteppingAction(TPCEventAction* eventAction);
    virtual ~TPCSteppingAction();

    sa_Config loadConfig();
    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    TPCEventAction*  fEventAction;

    std::ofstream myMWPCp    ;
    std::ofstream myTPCp     ;
    std::ofstream myMWPC     ;
    std::ofstream myTPC      ;
    std::ofstream myGen      ;
    std::ofstream myRest     ;
    std::ofstream myEnd      ;
    std::ifstream configFile ;

    int SimMode              ;
    int TrackProtons         ;
    G4LogicalVolume*  fTPC   ;
    G4LogicalVolume*  fSci   ;
    G4LogicalVolume*  fShi   ;
    G4LogicalVolume*  fFln   ;
    G4LogicalVolume*  fEnd   ;

    sa_Config config;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
