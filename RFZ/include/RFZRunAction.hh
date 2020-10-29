#ifndef RFZRunAction_h
#define RFZRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class RFZRunAction : public G4UserRunAction
{
  public:
    RFZRunAction();
    virtual ~RFZRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

