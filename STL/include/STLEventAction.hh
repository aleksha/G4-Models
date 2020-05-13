#ifndef STLEventAction_h
#define STLEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class STLRunAction;

/// Event action class
///

class STLEventAction : public G4UserEventAction
{
  public:
    STLEventAction(STLRunAction* runAction);
    virtual ~STLEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    STLRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

