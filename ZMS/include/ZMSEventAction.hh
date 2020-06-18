#ifndef ZMSEventAction_h
#define ZMSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class ZMSRunAction;

/// Event action class
///

class ZMSEventAction : public G4UserEventAction
{
  public:
    ZMSEventAction(ZMSRunAction* runAction);
    virtual ~ZMSEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    ZMSRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

