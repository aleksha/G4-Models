//------------------------------------------------------------------------------
#include "POSActionInitialization.hh"
#include "POSPrimaryGeneratorAction.hh"
#include "POSRunAction.hh"
#include "POSEventAction.hh"
#include "POSSteppingAction.hh"
//------------------------------------------------------------------------------
POSActionInitialization::POSActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
POSActionInitialization::~POSActionInitialization(){}
//------------------------------------------------------------------------------
void POSActionInitialization::BuildForMaster() const
{
  POSRunAction* runAction = new POSRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void POSActionInitialization::Build() const
{
  SetUserAction(new POSPrimaryGeneratorAction);

  POSRunAction* runAction = new POSRunAction;
  SetUserAction(runAction);

  POSEventAction* eventAction = new POSEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new POSSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
