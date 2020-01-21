//------------------------------------------------------------------------------
#include "EPSActionInitialization.hh"
#include "EPSPrimaryGeneratorAction.hh"
#include "EPSRunAction.hh"
#include "EPSEventAction.hh"
#include "EPSSteppingAction.hh"
//------------------------------------------------------------------------------
EPSActionInitialization::EPSActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
EPSActionInitialization::~EPSActionInitialization(){}
//------------------------------------------------------------------------------
void EPSActionInitialization::BuildForMaster() const
{
  EPSRunAction* runAction = new EPSRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void EPSActionInitialization::Build() const
{
  SetUserAction(new EPSPrimaryGeneratorAction);

  EPSRunAction* runAction = new EPSRunAction;
  SetUserAction(runAction);

  EPSEventAction* eventAction = new EPSEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new EPSSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
