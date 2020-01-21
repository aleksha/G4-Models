#include "EPSEventAction.hh"
#include "EPSRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
EPSEventAction::EPSEventAction(EPSRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
EPSEventAction::~EPSEventAction(){}
//------------------------------------------------------------------------------
void EPSEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void EPSEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
