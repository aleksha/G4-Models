#include "POSEventAction.hh"
#include "POSRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
POSEventAction::POSEventAction(POSRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
POSEventAction::~POSEventAction(){}
//------------------------------------------------------------------------------
void POSEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void POSEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
