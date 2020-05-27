#ifndef POSEventAction_h
#define POSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class POSRunAction;

/// Event action class
///

class POSEventAction : public G4UserEventAction
{
  public:
    POSEventAction(POSRunAction* runAction);
    virtual ~POSEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    POSRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

