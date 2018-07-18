//------------------------------------------------------------------------------
#include "CSCActionInitialization.hh"
#include "CSCPrimaryGeneratorAction.hh"
#include "CSCRunAction.hh"
#include "CSCEventAction.hh"
#include "CSCSteppingAction.hh"
//------------------------------------------------------------------------------
CSCActionInitialization::CSCActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
CSCActionInitialization::~CSCActionInitialization(){}
//------------------------------------------------------------------------------
void CSCActionInitialization::BuildForMaster() const
{
  CSCRunAction* runAction = new CSCRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void CSCActionInitialization::Build() const
{
  SetUserAction(new CSCPrimaryGeneratorAction);

  CSCRunAction* runAction = new CSCRunAction;
  SetUserAction(runAction);

  CSCEventAction* eventAction = new CSCEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new CSCSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
