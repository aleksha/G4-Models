#include "Sr90TESTSteppingAction.hh"
#include "Sr90TESTEventAction.hh"
#include "Sr90TESTDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTSteppingAction::Sr90TESTSteppingAction(Sr90TESTEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{
  myOUT.open( "out.data" , std::ios::trunc);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTSteppingAction::~Sr90TESTSteppingAction()
{
myOUT.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Sr90TESTSteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const Sr90TESTDetectorConstruction* detectorConstruction
      = static_cast<const Sr90TESTDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  double tr_ed = step->GetTotalEnergyDeposit() - step->GetNonIonizingEnergyDeposit() ;

  G4StepPoint* pre_step  ; pre_step  = step->GetPreStepPoint()  ;
  G4StepPoint* post_step ; post_step = step->GetPostStepPoint() ;

  double tr_post_x   = post_step->GetPosition().x() / mm ;
  double tr_post_y   = post_step->GetPosition().y() / mm ;
  double tr_post_z   = post_step->GetPosition().z() / mm ;
  //double g_post_time = post_step->GetGlobalTime ()  / ns ;

  double tr_pre_x   = pre_step->GetPosition().x() / mm ;
  double tr_pre_y   = pre_step->GetPosition().y() / mm ;
  double tr_pre_z   = pre_step->GetPosition().z() / mm ;
  //double g_pre_time = pre_step->GetGlobalTime ()  / ns ;

  double tr_x   =  0.5 * (tr_pre_x + tr_post_x);
  double tr_y   =  0.5 * (tr_pre_y + tr_post_y);
  double tr_z   =  0.5 * (tr_pre_z + tr_post_z);
  //double g_time =  0.5 * (g_pre_time + g_post_time);

  double dist = sqrt(tr_x*tr_x+tr_y*tr_y); // MWPC insesative area

//  if( myOUT.is_open() && step->IsLastStepInVolume()){
//    myOUT << tr_post_x  << " " << tr_post_y  << " " << tr_post_z  << " " << dist << " " << tr_ed <<  G4endl;
//  }

  if( myOUT.is_open() && dist > 0 && tr_ed>0 ){
    myOUT << tr_x  << " " << tr_y  << " " << tr_z  << " " << dist << " " << tr_ed <<  G4endl;
  }

  fEventAction->AddEdep(edepStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

