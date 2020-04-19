#ifndef Sr90TESTSteppingAction_h
#define Sr90TESTSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Sr90TESTEventAction;

class G4LogicalVolume;

class Sr90TESTSteppingAction : public G4UserSteppingAction
{
  public:
    Sr90TESTSteppingAction(Sr90TESTEventAction* eventAction);
    virtual ~Sr90TESTSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    Sr90TESTEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
    std::ofstream myOUT;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
