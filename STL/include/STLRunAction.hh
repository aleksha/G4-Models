#ifndef STLRunAction_h
#define STLRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class STLRunAction : public G4UserRunAction
{
  public:
    STLRunAction();
    virtual ~STLRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

