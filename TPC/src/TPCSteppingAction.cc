#include "TPCSteppingAction.hh"
#include "TPCEventAction.hh"
#include "TPCDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCSteppingAction::TPCSteppingAction(TPCEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fTPC (0),
  fSci (0),
  fFln (0),
  fShi (0),
  fEnd (0)
{
  config = loadConfig();

  configFile.open("genCONFIG.txt", std::ios::in);
  int config_id; 
  double config_value;
  while(configFile >> config_id >> config_value){
   if(config_id== 4){SimMode      = config_value;}
   if(config_id==14){TrackProtons = config_value;}
  }
  configFile.close();

  if( SimMode==0.0 ){
    myGen .open( "inTPC.data"  , std::ios::trunc);
    myRest.open( "rest.data"   , std::ios::trunc);
    myEnd .open( "end.data"    , std::ios::trunc);
  }
  if( SimMode==3.0  ){
    myTPC .open( "outTPC.data" , std::ios::trunc);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCSteppingAction::~TPCSteppingAction()
{

  if(SimMode==0.0){
    myGen .close();
    myRest.close();
  }
  if(SimMode==3.0 ){
    myTPC .close();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

sa_Config TPCSteppingAction::loadConfig()
{
  sa_Config tconfig;
  std::ifstream fin("config.txt");
  std::string line;
  while (getline(fin, line)) {
    std::istringstream sin(line.substr(line.find("=") + 1));
    if      (line.find("N_ev")         != 18446744073709551615ull ) sin >> tconfig.N_ev         ;
    else if (line.find("E_e")          != 18446744073709551615ull ) sin >> tconfig.E_e          ;
    else if (line.find("Tp")           != 18446744073709551615ull ) sin >> tconfig.Tp           ;
    else if (line.find("zTPC")         != 18446744073709551615ull ) sin >> tconfig.zTPC         ;
    else if (line.find("MatMode")      != 18446744073709551615ull ) sin >> tconfig.MatMode      ;
    else if (line.find("lTPC")         != 18446744073709551615ull ) sin >> tconfig.lTPC         ;
    else if (line.find("Pressure")     != 18446744073709551615ull ) sin >> tconfig.Pressure     ;
    else if (line.find("BeWindow")     != 18446744073709551615ull ) sin >> tconfig.BeWindow     ;
    else if (line.find("BeamSmearing") != 18446744073709551615ull ) sin >> tconfig.BeamSmearing ;
    else if (line.find("BeamTheta")    != 18446744073709551615ull ) sin >> tconfig.BeamTheta    ;
    else if (line.find("BeamPos")      != 18446744073709551615ull ) sin >> tconfig.BeamPos      ;

  }
  return tconfig;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCSteppingAction::UserSteppingAction(const G4Step* step)
{


  if ( !fTPC || !fSci || !fShi || !fEnd || !fFln ) { 
    const TPCDetectorConstruction* detectorConstruction = static_cast<const TPCDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fTPC   = detectorConstruction->GetTPC();   
    fSci   = detectorConstruction->GetSci();   
    fShi   = detectorConstruction->GetShi();   
    fFln   = detectorConstruction->GetShi();   
    fEnd   = detectorConstruction->GetEnd();   
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
      
  int vol = 0;
  // check if we are in scoring volume
  if (volume == fSci)   vol=1;
  if (volume == fTPC)   vol=2;
  if (volume == fEnd)   vol=3;
  if (volume == fShi)   vol=4;
  if (volume == fFln)   vol=5;
  
  if (vol<1 || vol>5) return ;
  
  G4Track* trk = step->GetTrack();
  int    ev_id = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() ;
  int    tr_id = trk->GetTrackID() ;
  int    tr_c  = trk->GetDefinition()->GetPDGCharge();
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
  
    //double dist = sqrt(tr_x*tr_x+tr_y*tr_y); // MWPC insesative area
    
/*
    if( myGen.is_open() && SimMode==0.0 && vol==2 && st_id==2 ){
      myGen  << ev_id      << " " << tr_px     << " " << tr_py       << " "
             << tr_pz      << " " << tr_m      << " " << tr_post_x   << " "
             << tr_post_y  << " " << tr_post_z << " " << g_post_time << " " 
             << p_code     << " " << tr_id << G4endl;
    }
*/
    if( myGen.is_open() && SimMode==0.0 && vol==2 && st_id==2 && false ){
      myGen  << ev_id      << " " << tr_px     << " " << tr_py       << " "
             << tr_pz      << " " << tr_m      << " " << tr_post_x   << " "
             << tr_post_y  << " " << tr_post_z << " " << g_post_time << " " 
             << p_code     << " " << tr_id << G4endl;

    }


    if( myRest.is_open() && SimMode==0.0 && vol==2 && tr_id>0 && true){
      myRest << ev_id << " " << tr_id << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_ed << G4endl;
    }

    if( myRest.is_open() && SimMode==0.0 && vol==5 && (st_id>0 && st_id<3) && tr_id>0 && false){
      myRest << ev_id     << " " << tr_id     << " " << st_id     << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_ed     << " " << p_code    << " " << tr_c      << " " << tr_e << G4endl;
    }

    if( myEnd.is_open() && SimMode==0.0 && ( vol==1 || vol==3 ) && tr_id==1 && false){
      myEnd  << ev_id     << " " << tr_id     << " " << vol       << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_ed << G4endl;
    }


    if( myTPC.is_open() &&  SimMode==3.0  && TrackProtons>0 && false){
      myTPC  << ev_id << " " << tr_id << " "
             << tr_pre_x  << " " << tr_pre_y  << " " << tr_pre_z  << " " << g_pre_time  << " "
             << tr_post_x << " " << tr_post_y << " " << tr_post_z << " " << g_post_time << " "
             << tr_ed  << " " << p_code  << " " << vol << G4endl;
    }


  }

  else{ return; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

