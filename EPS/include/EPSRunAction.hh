#ifndef EPSRunAction_h
#define EPSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class EPSRunAction : public G4UserRunAction
{
  public:
    EPSRunAction();
    virtual ~EPSRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

