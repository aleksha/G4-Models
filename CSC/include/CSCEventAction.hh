#ifndef CSCEventAction_h
#define CSCEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class CSCRunAction;

/// Event action class
///

class CSCEventAction : public G4UserEventAction
{
  public:
    CSCEventAction(CSCRunAction* runAction);
    virtual ~CSCEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    CSCRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

