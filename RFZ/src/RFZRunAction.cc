#include "RFZRunAction.hh"
#include "RFZPrimaryGeneratorAction.hh"
#include "RFZDetectorConstruction.hh"
// #include "RFZRun.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
RFZRunAction::RFZRunAction(): G4UserRunAction(){}
//------------------------------------------------------------------------------
RFZRunAction::~RFZRunAction(){}
//------------------------------------------------------------------------------
void RFZRunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}
//------------------------------------------------------------------------------
void RFZRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4cout  << "--------------------End of Run------------------------------"
          << G4endl
          << " The run consists of " << nofEvents << G4endl;
}
//------------------------------------------------------------------------------
