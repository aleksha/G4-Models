//------------------------------------------------------------------------------
#include "RFZActionInitialization.hh"
#include "RFZPrimaryGeneratorAction.hh"
#include "RFZRunAction.hh"
#include "RFZEventAction.hh"
#include "RFZSteppingAction.hh"
//------------------------------------------------------------------------------
RFZActionInitialization::RFZActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
RFZActionInitialization::~RFZActionInitialization(){}
//------------------------------------------------------------------------------
void RFZActionInitialization::BuildForMaster() const
{
  RFZRunAction* runAction = new RFZRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void RFZActionInitialization::Build() const
{
  SetUserAction(new RFZPrimaryGeneratorAction);

  RFZRunAction* runAction = new RFZRunAction;
  SetUserAction(runAction);

  RFZEventAction* eventAction = new RFZEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new RFZSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
