//------------------------------------------------------------------------------
#include "ZMSActionInitialization.hh"
#include "ZMSPrimaryGeneratorAction.hh"
#include "ZMSRunAction.hh"
#include "ZMSEventAction.hh"
#include "ZMSSteppingAction.hh"
//------------------------------------------------------------------------------
ZMSActionInitialization::ZMSActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
ZMSActionInitialization::~ZMSActionInitialization(){}
//------------------------------------------------------------------------------
void ZMSActionInitialization::BuildForMaster() const
{
  ZMSRunAction* runAction = new ZMSRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void ZMSActionInitialization::Build() const
{
  SetUserAction(new ZMSPrimaryGeneratorAction);

  ZMSRunAction* runAction = new ZMSRunAction;
  SetUserAction(runAction);

  ZMSEventAction* eventAction = new ZMSEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new ZMSSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
