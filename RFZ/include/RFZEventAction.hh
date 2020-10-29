#ifndef RFZEventAction_h
#define RFZEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RFZRunAction;

/// Event action class
///

class RFZEventAction : public G4UserEventAction
{
  public:
    RFZEventAction(RFZRunAction* runAction);
    virtual ~RFZEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    RFZRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

