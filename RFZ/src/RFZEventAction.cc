#include "RFZEventAction.hh"
#include "RFZRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
RFZEventAction::RFZEventAction(RFZRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
RFZEventAction::~RFZEventAction(){}
//------------------------------------------------------------------------------
void RFZEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void RFZEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
