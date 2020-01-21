#include "CSCEventAction.hh"
#include "CSCRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
CSCEventAction::CSCEventAction(CSCRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
CSCEventAction::~CSCEventAction(){}
//------------------------------------------------------------------------------
void CSCEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void CSCEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
