#ifndef TPCEventAction_h
#define TPCEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "g4root.hh"

class TPCRunAction;

/// Event action class
///

class TPCEventAction : public G4UserEventAction
{
  public:
    TPCEventAction(TPCRunAction* runAction);
    virtual ~TPCEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    TPCRunAction* fRunAction;
    G4double     fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
