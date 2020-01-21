#ifndef EPSEventAction_h
#define EPSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class EPSRunAction;

/// Event action class
///

class EPSEventAction : public G4UserEventAction
{
  public:
    EPSEventAction(EPSRunAction* runAction);
    virtual ~EPSEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    EPSRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

