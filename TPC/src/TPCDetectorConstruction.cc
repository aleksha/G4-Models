#include "TPCDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCDetectorConstruction::TPCDetectorConstruction()
: G4VUserDetectorConstruction(),
//  fScoringVolume(0)
  fTPC (0),
  fSci (0),
  fShi (0),
  fEnd (0)
/*  fBe1 (0),
  fSi1 (0),
  fSi2 (0),
  fPC_X1 (0),
  fPC_Y1 (0),
  fPC_X2 (0),
  fPC_Y2 (0)
*/
{

  config = loadConfig();

  zTPCFile.open("genCONFIG.txt", std::ios::in);
  int config_id; 
  double config_value;
  while(zTPCFile >> config_id >> config_value){
   if( config_id== 2 ){posTPC    = config_value;}
   if( config_id== 4 ){SimMode   = config_value;}
   if( config_id== 5 ){MatMode   = config_value;}
   if( config_id== 6 ){lengthTPC = config_value;}
   if( config_id== 7 ){BeWindow  = config_value;}
  }
  zTPCFile.close();

  if(SimMode > 0) {zTPC = lengthTPC;} else {zTPC = posTPC;}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCDetectorConstruction::~TPCDetectorConstruction()
{ }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dc_Config TPCDetectorConstruction::loadConfig()
{
  dc_Config tconfig;
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
    //G4cout << " N_EV " << sizeof( line.find("N_ev") ) << " "  << line.find("N_ev")  << G4endl;
  }
  return tconfig;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* TPCDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  G4int ncomponents, natoms;
  G4double fractionmass, density;
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* air_mat   = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* cu_mat    = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* al_mat    = nist->FindOrBuildMaterial("G4_Al");
  G4Material* be_mat    = nist->FindOrBuildMaterial("G4_Be");
  G4Material* si_mat    = nist->FindOrBuildMaterial("G4_Si");
  G4Material* steel_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  
  G4Element* H  = nist->FindOrBuildElement(1);
  G4Element* He = nist->FindOrBuildElement(2);
  G4Element* C  = nist->FindOrBuildElement(6);
  G4Element* N  = nist->FindOrBuildElement(7);
  G4Element* O  = nist->FindOrBuildElement(8);
  G4Element* Si = nist->FindOrBuildElement(14);

  G4Material* Kapton = new G4Material(name="Kapton", density=1.413*g/cm3, ncomponents=4 );
  Kapton->AddElement(O,natoms= 5); Kapton->AddElement(N,natoms= 2);
  Kapton->AddElement(C,natoms=22); Kapton->AddElement(H,natoms=10); 

  G4Material* G10 = new G4Material("G10", density=1.700*g/cm3, ncomponents=4);
  G10->AddElement(Si,natoms=1); G10->AddElement(O,natoms=2);
  G10->AddElement(C ,natoms=3); G10->AddElement(H,natoms=3);

  // Gas mixture: 96% He, 4%N2 (by volume) ; density: 0.179 / 1.250 ;  molar mass: 4.0026 / 14.00728*2
  G4Material* HeGas = new G4Material("HeGas", density=9.9*0.222*kg/m3, ncomponents=2);
  HeGas->AddElement(He, fractionmass=0.7748); HeGas->AddElement(N , fractionmass=0.2252);

//  G4Material *HeGas   = new G4Material("HeGas"  ,  1,  1.008  *g/mole,  1.6347*kg/m3 ); // 20 atm H2 = 1.6347*kg/m3 

  G4Material* SciSolid = new G4Material(name="SciSolid", density=1.032*g/cm3, ncomponents=2);
  SciSolid->AddElement(C, natoms=9); SciSolid->AddElement(H, natoms=10);


  G4bool ckOv = true;

  //     
  // Sizes
  //
  G4double world_sXY =   300.00*mm;
  G4double world_sZ  =  3500.00*mm;

  G4double i_gap     = 52.00*mm;
  G4double i_shift   =300.00*mm;
  G4double s_gap     = 50.00*mm;

  G4double si_sXY    =50.00*mm;
  G4double si_sZ     = 0.05*mm;

  G4double sc_sXY    =55.00*mm;
  G4double sc_sZ     = 2.00*mm;
  
  G4double be_sZ     = BeWindow*mm;
  G4double cu_sZ     = 0.02*mm;
  G4double an_sZ     = 1.50*mm;
  G4double ct_sZ     = 1.00*mm;
  G4double al_sZ     = 0.02*mm;


  G4double CU_sZ     = 0.05*mm;
  G4double KA_sZ     = 0.12*mm;

//------------>  G4double l_h1      =  365.+175*mm;  // IMPORTANT FIRST VERSION see E.Maev e-mail from 2017-03-28
//------------>  G4double l_w1      =  350.*mm;

  G4double l_h1      =  600.*mm;
  G4double l_w1      =  585.*mm;

  G4double l_h2      =  150.*mm;
  G4double l_h3      =   75.*mm;
  G4double lTPC      =  zTPC*mm;

  G4double l_w2      =  503.*mm;
  G4double l_f1      =   15.*mm; // length of 1st flange 1


  G4double r_h1      =  38.0*mm;
  G4double rTPC      = 144.0*mm;

  G4double w_w1      =   2.6*mm;
  G4double w_w2      =   4.0*mm; // width of 2nd wall

  G4Box* solidWorld = new G4Box ( "World", 0.5*world_sXY, 0.5*world_sXY, 0.5*world_sZ );
  G4Box* solidAir   = new G4Box ( "Air"  , 0.49999*world_sXY, 0.49999*world_sXY, 0.49999*world_sZ );
  
  G4Box* solidBW1   = new G4Box ( "BW1"  , 0.5*sc_sXY   , 0.5*sc_sXY   , 0.1*mm   );
  G4Box* solidShi   = new G4Box ( "Shi"  , 0.5*sc_sXY   , 0.5*sc_sXY   , 0.5*sc_sZ    );
  G4Box* solidSci   = new G4Box ( "Sci"  , 0.5*sc_sXY   , 0.5*sc_sXY   , 0.5*sc_sZ    );
  
  G4Box* solidSi1   = new G4Box ( "Si1"  , 0.5*si_sXY   , 0.5*si_sXY   , 0.5*si_sZ    );
  G4Box* solidSi2   = new G4Box ( "Si2"  , 0.5*si_sXY   , 0.5*si_sXY   , 0.5*si_sZ    );
  G4Box* solidSi3   = new G4Box ( "Si3"  , 0.5*si_sXY   , 0.5*si_sXY   , 0.5*si_sZ    );
  G4Box* solidSi4   = new G4Box ( "Si4"  , 0.5*si_sXY   , 0.5*si_sXY   , 0.5*si_sZ    );

  G4Tubs* solidBe1   = new G4Tubs( "Be1"   , 0.*mm, r_h1+w_w1, 0.5*be_sZ, 0.*deg, 360.*deg    );

  G4Tubs* solidCU    = new G4Tubs( "CU"    , 0.*mm, 20.*mm   , 0.5*CU_sZ, 0.*deg, 360.*deg    );
  G4Tubs* solidKA    = new G4Tubs( "KA"    , 0.*mm, 20.*mm   , 0.5*KA_sZ, 0.*deg, 360.*deg    );
  G4Tubs* solidCu1   = new G4Tubs( "Cu1"   ,20.*mm, rTPC     , 0.5*cu_sZ, 0.*deg, 360.*deg    );
  G4Tubs* solidAnod  = new G4Tubs( "Anod"  ,20.*mm, rTPC     , 0.5*an_sZ, 0.*deg, 360.*deg    );
  G4Tubs* solidCathod= new G4Tubs( "Cathod",20.*mm, rTPC     , 0.5*ct_sZ, 0.*deg, 360.*deg    );
//  G4Tubs* solidAl1   = new G4Tubs( "Al1"   , 0.*mm, 20.*mm   , 0.5*al_sZ, 0.*deg, 360.*deg    );

  G4Tubs* solid_h1  = new G4Tubs( "h1"   , 0.*mm, r_h1, 0.5*l_h1, 0.*deg, 360.*deg    );
  G4Tubs* solid_h2  = new G4Tubs( "h2"   , 0.*mm, rTPC, 0.5*l_h2, 0.*deg, 360.*deg    );
  G4Tubs* solidTPC  = new G4Tubs( "TPC"  , 0.*mm, rTPC, 0.5*lTPC, 0.*deg, 360.*deg    );
  G4Tubs* solid_h3  = new G4Tubs( "h3"   , 0.*mm, rTPC, 0.5*l_h3, 0.*deg, 360.*deg    );

  G4Tubs* solid_f1  = new G4Tubs( "f1"   ,   r_h1, rTPC+w_w2, 0.5*l_f1, 0.*deg, 360.*deg    );
  G4Tubs* solid_f2  = new G4Tubs( "f2"   , 20.*mm, rTPC+w_w2, 0.5*l_f1, 0.*deg, 360.*deg    );

  G4Tubs* solid_w1  = new G4Tubs( "w1"   , r_h1, r_h1+w_w1, 0.5*l_w1, 0.*deg, 360.*deg    );
  G4Tubs* solid_w2  = new G4Tubs( "w2"   , rTPC, rTPC+w_w2, 0.5*l_w2, 0.*deg, 360.*deg    );

  G4Tubs* solidBe2  = new G4Tubs( "Be2"   , 0.*mm, r_h1+w_w1, 0.5*be_sZ, 0.*deg, 360.*deg    );

  G4Box* solidEnd   = new G4Box ( "End"  , 0.5*sc_sXY   , 0.5*sc_sXY   , 0.5*sc_sZ    );


  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4LogicalVolume* logicAir   = new G4LogicalVolume(solidAir  , world_mat, "Air");


  G4LogicalVolume* logicBW1   = new G4LogicalVolume( solidBW1   , world_mat, "BW1"   );
  G4LogicalVolume* logicBe1   = new G4LogicalVolume( solidBe1   , world_mat, "Be1"   );
  G4LogicalVolume* logicAnod  = new G4LogicalVolume( solidAnod  , world_mat, "Anod"  );
  G4LogicalVolume* logicCu1   = new G4LogicalVolume( solidCu1   , world_mat, "Cu1"   );
  G4LogicalVolume* logicCU    = new G4LogicalVolume( solidCU    , world_mat, "CU"    );
  G4LogicalVolume* logicKA    = new G4LogicalVolume( solidKA    , world_mat, "KA"    );
  G4LogicalVolume* logicCathod= new G4LogicalVolume( solidCathod, world_mat, "Cathod");
//  G4LogicalVolume* logicAl1   = new G4LogicalVolume( solidAl1   , world_mat, "Al1"   );
  
  G4LogicalVolume* logicSci   = new G4LogicalVolume( solidSci , world_mat, "Sci" );
  G4LogicalVolume* logicShi   = new G4LogicalVolume( solidShi , world_mat, "Shi" );
  
  G4LogicalVolume* logicSi1   = new G4LogicalVolume( solidSi1 , world_mat, "Si1" );
  G4LogicalVolume* logicSi2   = new G4LogicalVolume( solidSi2 , world_mat, "Si2" );
  G4LogicalVolume* logicSi3   = new G4LogicalVolume( solidSi3 , world_mat, "Si3" );
  G4LogicalVolume* logicSi4   = new G4LogicalVolume( solidSi4 , world_mat, "Si4" );

  G4LogicalVolume* logic_f1   = new G4LogicalVolume( solid_f1 , world_mat, "f1"  );
  G4LogicalVolume* logic_f2   = new G4LogicalVolume( solid_f2 , world_mat, "f2"  );

  G4LogicalVolume* logic_w1   = new G4LogicalVolume( solid_w1 , world_mat, "w1"  );
  G4LogicalVolume* logic_w2   = new G4LogicalVolume( solid_w2 , world_mat, "w2"  );

  G4LogicalVolume* logic_h1   = new G4LogicalVolume( solid_h1 , world_mat, "h1"  );
  G4LogicalVolume* logic_h2   = new G4LogicalVolume( solid_h2 , world_mat, "h2"  );
  G4LogicalVolume* logicTPC   = new G4LogicalVolume( solidTPC , world_mat, "TPC" );
  G4LogicalVolume* logic_h3   = new G4LogicalVolume( solid_h3 , world_mat, "h3"  );
  G4LogicalVolume* logicBe2   = new G4LogicalVolume( solidBe2 , world_mat, "Be2" );
 
  G4LogicalVolume* logicEnd   = new G4LogicalVolume( solidEnd , world_mat, "End" );

  if(MatMode>0){
    logicAir   ->SetMaterial( air_mat   );

    logicBW1   ->SetMaterial( Kapton    );
    logicBe1   ->SetMaterial( be_mat    );
    logicAnod  ->SetMaterial( G10       );
    logicCu1   ->SetMaterial( cu_mat    );
    logicCU    ->SetMaterial( cu_mat    );
    logicKA    ->SetMaterial( Kapton    );
    logicCathod->SetMaterial( steel_mat );
//    logicAl1   ->SetMaterial( al_mat    );
  
    logicSci   ->SetMaterial( SciSolid  );
    logicShi   ->SetMaterial( SciSolid  );
    logicEnd   ->SetMaterial( SciSolid  );
    
    logicSi1   ->SetMaterial( si_mat    );
    logicSi2   ->SetMaterial( si_mat    );
    logicSi3   ->SetMaterial( si_mat    );
    logicSi4   ->SetMaterial( si_mat    );

    logic_f1   ->SetMaterial( steel_mat );
    logic_f2   ->SetMaterial( steel_mat );

    logic_w1   ->SetMaterial( steel_mat );
    logic_w2   ->SetMaterial( al_mat    );

    logic_h1   ->SetMaterial( HeGas     );
    logic_h2   ->SetMaterial( HeGas     );
    logicTPC   ->SetMaterial( HeGas     );
    logic_h3   ->SetMaterial( HeGas     );
    logicBe2   ->SetMaterial( be_mat    );

  }


  //G4cout << "\n\n\n\n" << l_h3 << " " << lTPC+0.5*l_h3 << " " << ct_sZ << " " << lTPC + 0.5*ct_sZ << "\n\n\n\n"<< G4endl;
  //G4cout << "\n\n\n\n" << l_h3 << " " << lTPC+0.5*l_h3 << " " << al_sZ << " " << lTPC + 0.5*al_sZ << "\n\n\n\n"<< G4endl;
  G4double lll      =  120.*mm;
  G4double sss      = l_h1 + l_h2 + s_gap + i_shift + be_sZ ; 
  G4double bbb      = 450.*mm; 
  G4double www      = bbb + sss - 0.5* world_sZ; 
  G4cout << "\n\n\n\n SSSS  " << sss << "\n\n\n\n"<< G4endl;
  G4cout << "\n\n\n\n WWWW  " << www << "\n\n\n\n"<< G4endl;
  G4double shift_x      =  50.*mm;
  G4ThreeVector world_pos ;  world_pos.set(0,0, 0                                );
  G4ThreeVector air_pos   ;    air_pos.set(0,0, 0                                );
  G4ThreeVector bw1_pos   ;    bw1_pos.set(0,0, -bbb -sss                        );
  G4ThreeVector si1_pos   ;    si1_pos.set(0,0, 0.*i_gap - sss                   );
  G4ThreeVector si2_pos   ;    si2_pos.set(0,0, 1.*i_gap - sss                   );
  G4ThreeVector si3_pos   ;    si3_pos.set(0,0, 2.*i_gap - sss                   );
  G4ThreeVector si4_pos   ;    si4_pos.set(0,0, 3.*i_gap - sss                   );
  G4ThreeVector sci_pos   ;    sci_pos.set(0,0, 0.5*sc_sZ-s_gap-be_sZ-l_h1-l_h2 );
  G4ThreeVector be1_pos   ;    be1_pos.set(0,0, -0.5*be_sZ-l_h1-l_h2             );
  G4ThreeVector w1_pos    ;     w1_pos.set(0,0, (l_w1-l_h1)-0.5*l_w1-l_h2        );
  G4ThreeVector h1_pos    ;     h1_pos.set(0,0, -0.5*l_h1-l_h2                   );
  G4ThreeVector f1_pos    ;     f1_pos.set(0,0, -0.5*l_f1-l_h2                   );
  G4ThreeVector w2_pos    ;     w2_pos.set(0,0,  0.5*l_w2-l_h2                   );
  G4ThreeVector h2_pos    ;     h2_pos.set(0,0, -0.5*l_h2                        );
  G4ThreeVector cu_pos    ;     cu_pos.set(0,0, -0.5*cu_sZ                       );
  G4ThreeVector anod_pos  ;   anod_pos.set(0,0, -0.5*an_sZ-cu_sZ                 );
  G4ThreeVector CU_pos    ;     CU_pos.set(0,0, -0.5*CU_sZ                       );
  G4ThreeVector KA_pos    ;     KA_pos.set(0,0, -0.5*KA_sZ - CU_sZ               );
  G4ThreeVector TPC_pos   ;    TPC_pos.set(0,0,  0.5*lTPC                        );
  G4ThreeVector h3_pos    ;     h3_pos.set(0,0,  0.5*l_h3 + lTPC                 );
  G4ThreeVector cathod_pos; cathod_pos.set(0,0,  0.5*ct_sZ + lTPC                );
  G4ThreeVector f2_pos    ;     f2_pos.set(0,0, lTPC+l_h3+0.5*l_f1            );
  G4ThreeVector be2_pos   ;    be2_pos.set(0,0, lTPC+l_h3+l_f1+0.5*be_sZ         );
  G4ThreeVector end_pos   ;    end_pos.set(0,0, lTPC+l_h3+l_f1+0.5*sc_sZ + lll   );
  G4ThreeVector shi_pos   ;    shi_pos.set(shift_x,0, lTPC+l_h3+l_f1+0.5*sc_sZ + lll + shift_x  );
                                   
  G4VPhysicalVolume* physWorld = 
     new G4PVPlacement(0, world_pos, logicWorld , "World" ,          0, false, 0, ckOv );
     new G4PVPlacement(0,   air_pos, logicAir   , "Air"   , logicWorld, false, 0, ckOv );
     new G4PVPlacement(0,   bw1_pos, logicBW1   , "BW1"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   si1_pos, logicSi1   , "Si1"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   si2_pos, logicSi2   , "Si2"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   si3_pos, logicSi3   , "Si3"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   si4_pos, logicSi4   , "Si4"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   sci_pos, logicSci   , "Sci"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   be1_pos, logicBe1   , "Be1"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    w1_pos, logic_w1   , "w1"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    h1_pos, logic_h1   , "h1"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    f1_pos, logic_f1   , "f1"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    w2_pos, logic_w2   , "w2"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    h2_pos, logic_h2   , "h2"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    cu_pos, logicCu1   , "Cu1"   , logic_h2  , false, 0, ckOv );
     new G4PVPlacement(0,  anod_pos, logicAnod  , "Anod"  , logic_h2  , false, 0, ckOv );
     new G4PVPlacement(0,    CU_pos, logicCU    , "CU"    , logic_h2  , false, 0, ckOv );
     new G4PVPlacement(0,    KA_pos, logicKA    , "KA"    , logic_h2  , false, 0, ckOv );
     new G4PVPlacement(0,   TPC_pos, logicTPC   , "TPC"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,    h3_pos, logic_h3   , "h3"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,cathod_pos, logicCathod, "Cathod", logic_h3  , false, 0, ckOv );
     new G4PVPlacement(0,    f2_pos, logic_f2   , "f2"    , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   be2_pos, logicBe2   , "Be2"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   end_pos, logicEnd   , "End"   , logicAir  , false, 0, ckOv );
     new G4PVPlacement(0,   shi_pos, logicShi   , "Shi"   , logicAir  , false, 0, ckOv );


  fTPC = logicTPC;
  fSci = logicSci;
  fShi = logicShi;
  fFln = logic_f2;
  fEnd = logicEnd;


  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
