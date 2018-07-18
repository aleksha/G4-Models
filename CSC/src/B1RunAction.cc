#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
// #include "B1Run.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
B1RunAction::B1RunAction(): G4UserRunAction(){}
//------------------------------------------------------------------------------
B1RunAction::~B1RunAction(){}
//------------------------------------------------------------------------------
void B1RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}
//------------------------------------------------------------------------------
void B1RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4cout  << "--------------------End of Run------------------------------"
          << G4endl
          << " The run consists of " << nofEvents << G4endl;
}
//------------------------------------------------------------------------------
