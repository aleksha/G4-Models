#ifndef EPSSteppingAction_h
#define EPSSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class EPSEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class EPSSteppingAction : public G4UserSteppingAction
{
  public:
    EPSSteppingAction(EPSEventAction* eventAction);
    virtual ~EPSSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    EPSEventAction*  fEventAction;
    std::ofstream myOUT;

    G4LogicalVolume* fLV00;
    G4LogicalVolume* fLV01;
    G4LogicalVolume* fLV02;
    G4LogicalVolume* fLV03;
    G4LogicalVolume* fLV04;
    G4LogicalVolume* fLV05;
    G4LogicalVolume* fLV06;
    G4LogicalVolume* fLV07;
    G4LogicalVolume* fLV08;
    G4LogicalVolume* fLV09;
    G4LogicalVolume* fLV10;
    G4LogicalVolume* fLV11;
    G4LogicalVolume* fLV12;
    G4LogicalVolume* fLV13;
    G4LogicalVolume* fLV14;
    G4LogicalVolume* fLV15;
    G4LogicalVolume* fLV16;
};
//------------------------------------------------------------------------------
#endif
