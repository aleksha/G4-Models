//------------------------------------------------------------------------------
#include "STLActionInitialization.hh"
#include "STLPrimaryGeneratorAction.hh"
#include "STLRunAction.hh"
#include "STLEventAction.hh"
#include "STLSteppingAction.hh"
//------------------------------------------------------------------------------
STLActionInitialization::STLActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
STLActionInitialization::~STLActionInitialization(){}
//------------------------------------------------------------------------------
void STLActionInitialization::BuildForMaster() const
{
  STLRunAction* runAction = new STLRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void STLActionInitialization::Build() const
{
  SetUserAction(new STLPrimaryGeneratorAction);

  STLRunAction* runAction = new STLRunAction;
  SetUserAction(runAction);

  STLEventAction* eventAction = new STLEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new STLSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
