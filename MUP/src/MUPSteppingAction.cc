
#include "MUPSteppingAction.hh"
#include "MUPEventAction.hh"
#include "MUPDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
MUPSteppingAction::MUPSteppingAction(MUPEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0)
{
 myOUT .open( "out.data" , std::ios::trunc);
}
//------------------------------------------------------------------------------
MUPSteppingAction::~MUPSteppingAction(){
  myOUT.close(); }
//------------------------------------------------------------------------------
void MUPSteppingAction::UserSteppingAction(const G4Step* step)
{
  if ( !fLV00 || !fLV01 || !fLV02 || !fLV03 ){
    const MUPDetectorConstruction* detectorConstruction
      = static_cast<const MUPDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fLV00 = detectorConstruction->GetLV00();
    fLV01 = detectorConstruction->GetLV01();
    fLV02 = detectorConstruction->GetLV02();
    fLV03 = detectorConstruction->GetLV03();
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
                                           ->GetVolume()->GetLogicalVolume();


  int vol = -1;
  // check if we are in scoring volume
  if (volume == fLV00) vol = 0 ;
  if (volume == fLV01) vol = 1 ;
  if (volume == fLV02) vol = 2 ;
  if (volume == fLV03) vol = 3 ;

  if ( vol == -1 ) return;

  G4Track* trk = step->GetTrack();
  int    tr_c  = trk->GetDefinition()->GetPDGCharge();


  int    ev_id = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() ;
  int    tr_id = trk->GetTrackID() ;
  double tr_m  = trk->GetDefinition()->GetPDGMass()  ;
  G4int p_code = trk->GetDefinition()->GetPDGEncoding();

  int st_id = 0;
  if( step->IsFirstStepInVolume() ){ st_id = 1; }
  if( step->IsLastStepInVolume()  ){ st_id = 2; }
  if( trk->GetKineticEnergy ()==0 ){ st_id = 3; }


  if(st_id>-1){
    G4StepPoint* pre_step  ; pre_step  = step->GetPreStepPoint()  ;
    G4StepPoint* post_step ; post_step = step->GetPostStepPoint() ;
    double tr_ed = step->GetTotalEnergyDeposit() - step->GetNonIonizingEnergyDeposit() ;
    //double tr_rd = step->GetNonIonizingEnergyDeposit() ;

    double tr_px  = post_step->GetMomentum().x()      ;
    double tr_py  = post_step->GetMomentum().y()      ;
    double tr_pz  = post_step->GetMomentum().z()      ;
    double tr_e   = post_step->GetTotalEnergy ()      ;
    //double tr_t   = post_step->GetKineticEnergy ()    ;
    double tr_post_x   = post_step->GetPosition().x() / mm ;
    double tr_post_y   = post_step->GetPosition().y() / mm ;
    double tr_post_z   = post_step->GetPosition().z() / mm ;
    double g_post_time = post_step->GetGlobalTime ()  / ns ;

    double tr_pre_x   = pre_step->GetPosition().x() / mm ;
    double tr_pre_y   = pre_step->GetPosition().y() / mm ;
    double tr_pre_z   = pre_step->GetPosition().z() / mm ;
    double g_pre_time = pre_step->GetGlobalTime ()  / ns ;

    double tr_x   =  0.5 * (tr_pre_x + tr_post_x);
    double tr_y   =  0.5 * (tr_pre_y + tr_post_y);
    double tr_z   =  0.5 * (tr_pre_z + tr_post_z);
    double g_time =  0.5 * (g_pre_time + g_post_time);

    if(myOUT.is_open() && vol>-1 && st_id==2)
       myOUT << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_ed<< " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_px     << " " << tr_py     << " " << tr_pz     << " " << tr_m
             << G4endl;

//    if(myOUT.is_open() && vol>-1 && vol<4 && st_id==2 && tr_id==1)
//       myOUT << ev_id  << " " << vol  << " "
//             << tr_post_x << " " << tr_post_y << " " << tr_post_z
//             << G4endl;

  }

//  // collect energy deposited in this step
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddEdep(edepStep);
}
//------------------------------------------------------------------------------

