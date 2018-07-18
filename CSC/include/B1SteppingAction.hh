#ifndef CSCSteppingAction_h
#define CSCSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class CSCEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class CSCSteppingAction : public G4UserSteppingAction
{
  public:
    CSCSteppingAction(CSCEventAction* eventAction);
    virtual ~CSCSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    CSCEventAction*  fEventAction;
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
