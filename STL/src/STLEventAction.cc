#include "STLEventAction.hh"
#include "STLRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
STLEventAction::STLEventAction(STLRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
STLEventAction::~STLEventAction(){}
//------------------------------------------------------------------------------
void STLEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void STLEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
