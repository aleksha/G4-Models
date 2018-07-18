
#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fLV0(0), fLV1(0), fLV2(0), fLV3(0), fLV4(0),
  fLV5(0), fLV6(0), fLV7(0), fLV8(0), fLV9(0)
{
 myOUT .open( "out.data" , std::ios::trunc);
 myINI .open( "ini.data" , std::ios::trunc);
 myCSC .open( "csc.data" , std::ios::trunc);
}
//------------------------------------------------------------------------------
B1SteppingAction::~B1SteppingAction(){ myOUT.close(); myCSC.close(); myINI.close();}
//------------------------------------------------------------------------------
void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if ( !fLV0 || !fLV1 || !fLV2 || !fLV3 || !fLV4 ||
                !fLV5 || !fLV6 || !fLV7 || !fLV8 || !fLV9 ) {
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fLV0 = detectorConstruction->GetLV0();
    fLV1 = detectorConstruction->GetLV1();
    fLV2 = detectorConstruction->GetLV2();
    fLV3 = detectorConstruction->GetLV3();
    fLV4 = detectorConstruction->GetLV4();
    fLV5 = detectorConstruction->GetLV5();
    fLV6 = detectorConstruction->GetLV6();
    fLV7 = detectorConstruction->GetLV7();
    fLV8 = detectorConstruction->GetLV8();
    fLV9 = detectorConstruction->GetLV9();
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
                                           ->GetVolume()->GetLogicalVolume();


  int vol=-1;
  // check if we are in scoring volume
  if (volume == fLV0) vol=0 ;
  if (volume == fLV1) vol=1 ;
  if (volume == fLV2) vol=2 ;
  if (volume == fLV3) vol=3 ;
  if (volume == fLV4) vol=4 ;
  if (volume == fLV5) vol=5 ;
  if (volume == fLV6) vol=6 ;
  if (volume == fLV7) vol=7 ;
  if (volume == fLV8) vol=8 ;
  if (volume == fLV9) vol=9 ;

  if (vol<0 || vol>7) return;

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

    //double tr_x   =  0.5 * (tr_pre_x + tr_post_x);
    //double tr_y   =  0.5 * (tr_pre_y + tr_post_y);
    //double tr_z   =  0.5 * (tr_pre_z + tr_post_z);
    //double g_time =  0.5 * (g_pre_time + g_post_time);

    if(myOUT.is_open() && vol==4 && st_id==2)
       myOUT << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_px     << " " << tr_py     << " " << tr_pz     << " " << tr_m
             << G4endl;

    if(myINI.is_open() && vol==5 && st_id==2 )
       myINI << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_px     << " " << tr_py     << " " << tr_pz     << " " << tr_m
             << G4endl;

    if(myCSC.is_open() && vol>5 && vol<8 && tr_ed>0)
       myCSC << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << G4endl;
  }

//  // collect energy deposited in this step
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddEdep(edepStep);
}
//------------------------------------------------------------------------------

