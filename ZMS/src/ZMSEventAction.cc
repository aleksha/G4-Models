#include "ZMSEventAction.hh"
#include "ZMSRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
ZMSEventAction::ZMSEventAction(ZMSRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
ZMSEventAction::~ZMSEventAction(){}
//------------------------------------------------------------------------------
void ZMSEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void ZMSEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
