#ifndef POSRunAction_h
#define POSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class POSRunAction : public G4UserRunAction
{
  public:
    POSRunAction();
    virtual ~POSRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

