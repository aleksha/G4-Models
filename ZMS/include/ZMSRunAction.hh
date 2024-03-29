#ifndef ZMSRunAction_h
#define ZMSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class ZMSRunAction : public G4UserRunAction
{
  public:
    ZMSRunAction();
    virtual ~ZMSRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

