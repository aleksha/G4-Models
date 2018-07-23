
#include "TPCEventAction.hh"
#include "TPCRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "g4root.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCEventAction::TPCEventAction(TPCRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCEventAction::~TPCEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCEventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  //G4AnalysisManager* man = G4AnalysisManager::Instance();
  //man->FillH1(1, fEdep);
  fRunAction->AddEdep(fEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
