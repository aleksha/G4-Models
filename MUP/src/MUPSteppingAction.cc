
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
  fLV00(0), fLV01(0), fLV02(0), fLV03(0), fLV04(0),
  fLV05(0), fLV06(0), fLV07(0), fLV08(0), fLV09(0),
  fLV10(0), fLV11(0), fLV12(0), fLV13(0), fLV14(0),
  fLV15(0), fLV16(0)
{
 myOUT .open( "out.data" , std::ios::trunc);
 myINI .open( "ini.data" , std::ios::trunc);
 myMUP .open( "csc.data" , std::ios::trunc);
 mySCI .open( "sci.data" , std::ios::trunc);
}
//------------------------------------------------------------------------------
MUPSteppingAction::~MUPSteppingAction(){
  myOUT.close(); myMUP.close(); myINI.close(); mySCI.close(); }
//------------------------------------------------------------------------------
void MUPSteppingAction::UserSteppingAction(const G4Step* step)
{
  if ( !fLV00 || !fLV01 || !fLV02 || !fLV03 || !fLV04 ||
                 !fLV05 || !fLV06 || !fLV07 || !fLV08 || !fLV09 ||
       !fLV10 || !fLV11 || !fLV12 || !fLV13 || !fLV14 || !fLV15 || !fLV16 ){
    const MUPDetectorConstruction* detectorConstruction
      = static_cast<const MUPDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fLV00 = detectorConstruction->GetLV00();
    fLV01 = detectorConstruction->GetLV01();
    fLV02 = detectorConstruction->GetLV02();
    fLV03 = detectorConstruction->GetLV03();
    fLV04 = detectorConstruction->GetLV04();
    fLV05 = detectorConstruction->GetLV05();
    fLV06 = detectorConstruction->GetLV06();
    fLV07 = detectorConstruction->GetLV07();
    fLV08 = detectorConstruction->GetLV08();
    fLV09 = detectorConstruction->GetLV09();
    fLV10 = detectorConstruction->GetLV10();
    fLV11 = detectorConstruction->GetLV11();
    fLV12 = detectorConstruction->GetLV12();
    fLV13 = detectorConstruction->GetLV13();
    fLV14 = detectorConstruction->GetLV14();
    fLV15 = detectorConstruction->GetLV15();
    fLV16 = detectorConstruction->GetLV16();
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
                                           ->GetVolume()->GetLogicalVolume();


  int vol=-1;
  // check if we are in scoring volume
  if (volume == fLV00) vol= 0 ;
  if (volume == fLV01) vol= 1 ;
  if (volume == fLV02) vol= 2 ;
  if (volume == fLV03) vol= 3 ;
  if (volume == fLV04) vol= 4 ;
  if (volume == fLV05) vol= 5 ;
  if (volume == fLV06) vol= 6 ;
  if (volume == fLV07) vol= 7 ;
  if (volume == fLV08) vol= 8 ;
  if (volume == fLV09) vol= 9 ;
  if (volume == fLV10) vol=10 ;
  if (volume == fLV11) vol=11 ;
  if (volume == fLV12) vol=12 ;
  if (volume == fLV13) vol=13 ;
  if (volume == fLV14) vol=14 ;
  if (volume == fLV15) vol=15 ;
  if (volume == fLV16) vol=16 ;

//  if (vol!=0 || vol!=5 || vol!=6 || vol!=7 || vol!=8 || vol!=15) return;

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

    if(myOUT.is_open() && vol==5 && st_id==2)
       myOUT << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_px     << " " << tr_py     << " " << tr_pz     << " " << tr_m
             << G4endl;

    if(myINI.is_open() && vol==6 && st_id==2 )
       myINI << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_px     << " " << tr_py     << " " << tr_pz     << " " << tr_m
             << G4endl;

    if(myMUP.is_open() && vol>6 && vol<9 && tr_ed>0)
       myMUP << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << G4endl;

    if(mySCI.is_open() && (vol==0 || vol==6 || vol==15 || vol==16) && tr_ed>0){

       if( ( (vol==0 || vol==15 || vol==16) && (tr_x>-30 && tr_x<30) &&  (tr_y>-30 && tr_y<30) ) ||
           ( vol==6 && tr_x>-30 && tr_x<30 && tr_y>-300 && tr_y<300                 )    ){
           mySCI << ev_id     << " " << tr_id     << " " << st_id     << " " << vol  << " "
                 << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << " "
                 << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
                 << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
                 << G4endl;}
    }
  }

//  // collect energy deposited in this step
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddEdep(edepStep);
}
//------------------------------------------------------------------------------

