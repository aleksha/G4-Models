#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class B1EventAction;

class G4LogicalVolume;

/// Stepping action class
///

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    B1EventAction*  fEventAction;
    std::ofstream myOUT;
    std::ofstream myINI;
    std::ofstream myCSC;

    G4LogicalVolume* fLV0;
    G4LogicalVolume* fLV1;
    G4LogicalVolume* fLV2;
    G4LogicalVolume* fLV3;
    G4LogicalVolume* fLV4;
    G4LogicalVolume* fLV5;
    G4LogicalVolume* fLV6;
    G4LogicalVolume* fLV7;
    G4LogicalVolume* fLV8;
    G4LogicalVolume* fLV9;
};
//------------------------------------------------------------------------------
#endif
