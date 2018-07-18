#ifndef CSCRunAction_h
#define CSCRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class CSCRunAction : public G4UserRunAction
{
  public:
    CSCRunAction();
    virtual ~CSCRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

