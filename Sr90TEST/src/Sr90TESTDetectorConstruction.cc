#include "Sr90TESTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTDetectorConstruction::Sr90TESTDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTDetectorConstruction::~Sr90TESTDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* Sr90TESTDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* air_mat   = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* sr_mat    = nist->FindOrBuildMaterial("G4_Sr");
  G4Material* steel_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* plexi_mat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
  G4Material* pb_mat    = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* w_mat     = nist->FindOrBuildMaterial("G4_W");
  G4Material* cu_mat    = nist->FindOrBuildMaterial("G4_Cu");


  G4Element* H  = nist->FindOrBuildElement(1);
  G4Element* C  = nist->FindOrBuildElement(6);
  G4Element* O  = nist->FindOrBuildElement(8);
  G4Element* Si = nist->FindOrBuildElement(14);
  G4Material* g10_mat = new G4Material("G10", density=1.700*g/cm3, ncomponents=4);
  g10_mat->AddElement(Si,natoms=1); g10_mat->AddElement(O,natoms=2);
  g10_mat->AddElement(C ,natoms=3); g10_mat->AddElement(H,natoms=3);

  G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 1.784 *kg/m3 );

  G4double sr_R = 2*mm, sr_Z = 2*mm;
  G4double steel1_r = 1*mm, steel1_R = 3*mm;
  G4double w_Z = 0.1*mm;
  G4double steel2_Z = 6*mm;
  G4double plexi1_r = 3*mm, plexi1_R = 8*mm;
  G4double plexi1_Z = steel2_Z + sr_Z;
  G4double plexi2_Z = 20*mm;
  G4double pb1_r = 8*mm, pb1_R = 16*mm;
  G4double pb1_Z = plexi2_Z + steel2_Z + sr_Z;
  G4double pb2_Z = 8*mm;

  G4double cu_Z  =  0.035*mm;
  G4double g10_Z =  1.500*mm;
  G4double air_Z = 10.000*mm;
  G4double ar_Z  =  9.000*mm;

  G4double chamber_R  = 300.0*mm;

  G4double Zd  =   0.*deg;
  G4double Td  = 360.*deg;

  G4Tubs* sol_Sr  = new G4Tubs(  "Sr" ,    0.*mm,      sr_R ,     0.5*sr_Z, Zd, Td);
  G4Tubs* sol_st1 = new G4Tubs( "st1" , steel1_r,  steel1_R ,     0.5*sr_Z, Zd, Td);
  G4Tubs* sol_st2 = new G4Tubs( "st2" ,    0.*mm,  steel1_R , 0.5*steel2_Z, Zd, Td);
  G4Tubs* sol_pl1 = new G4Tubs( "pl1" , plexi1_r,  plexi1_R , 0.5*plexi1_Z, Zd, Td);
  G4Tubs* sol_pl2 = new G4Tubs( "pl2" ,    0.*mm,  plexi1_R , 0.5*plexi2_Z, Zd, Td);
  G4Tubs* sol_pb1 = new G4Tubs( "pb1" ,    pb1_r,     pb1_R ,    0.5*pb1_Z, Zd, Td);
  G4Tubs* sol_pb2 = new G4Tubs( "pb2" ,    0.*mm,     pb1_R ,    0.5*pb2_Z, Zd, Td);
  G4Tubs* sol_w   = new G4Tubs(   "W" ,    0.*mm,  steel1_R ,      0.5*w_Z, Zd, Td);
  G4Tubs* sol_cu1 = new G4Tubs( "cu1" ,    0.*mm, chamber_R ,     0.5*cu_Z, Zd, Td);
  G4Tubs* sol_cu2 = new G4Tubs( "cu2" ,    0.*mm, chamber_R ,     0.5*cu_Z, Zd, Td);
  G4Tubs* sol_cu3 = new G4Tubs( "cu3" ,    0.*mm, chamber_R ,     0.5*cu_Z, Zd, Td);
  G4Tubs* sol_cu4 = new G4Tubs( "cu4" ,    0.*mm, chamber_R ,     0.5*cu_Z, Zd, Td);
  G4Tubs* sol_gt1 = new G4Tubs( "gt1" ,    0.*mm, chamber_R ,    0.5*g10_Z, Zd, Td);
  G4Tubs* sol_gt2 = new G4Tubs( "gt2" ,    0.*mm, chamber_R ,    0.5*g10_Z, Zd, Td);
  G4Tubs* sol_gt3 = new G4Tubs( "gt3" ,    0.*mm, chamber_R ,    0.5*g10_Z, Zd, Td);
  G4Tubs* sol_gt4 = new G4Tubs( "gt4" ,    0.*mm, chamber_R ,    0.5*g10_Z, Zd, Td);
  G4Tubs* sol_ai1 = new G4Tubs( "ai1" ,    0.*mm, chamber_R ,    0.5*air_Z, Zd, Td);
  G4Tubs* sol_ai2 = new G4Tubs( "ai2" ,    0.*mm, chamber_R ,    0.5*air_Z, Zd, Td);
  G4Tubs* sol_Ar  = new G4Tubs(  "Ar" ,    0.*mm, chamber_R ,     0.5*ar_Z, Zd, Td);

  G4LogicalVolume* log_Sr   = new G4LogicalVolume( sol_Sr  ,    sr_mat,  "Sr");
  G4LogicalVolume* log_st1  = new G4LogicalVolume( sol_st1 , steel_mat, "st1");
  G4LogicalVolume* log_st2  = new G4LogicalVolume( sol_st2 , steel_mat, "st2");
  G4LogicalVolume* log_pl1  = new G4LogicalVolume( sol_pl1 , plexi_mat, "pl1");
  G4LogicalVolume* log_pl2  = new G4LogicalVolume( sol_pl2 , plexi_mat, "pl2");
  G4LogicalVolume* log_pb1  = new G4LogicalVolume( sol_pb1 ,    pb_mat, "pb1");
  G4LogicalVolume* log_pb2  = new G4LogicalVolume( sol_pb2 ,    pb_mat, "pb2");
  G4LogicalVolume* log_w    = new G4LogicalVolume( sol_w   ,     w_mat,   "W");
  G4LogicalVolume* log_cu1  = new G4LogicalVolume( sol_cu1 ,    cu_mat, "cu1");
  G4LogicalVolume* log_cu2  = new G4LogicalVolume( sol_cu2 ,    cu_mat, "cu2");
  G4LogicalVolume* log_cu3  = new G4LogicalVolume( sol_cu3 ,    cu_mat, "cu3");
  G4LogicalVolume* log_cu4  = new G4LogicalVolume( sol_cu4 ,    cu_mat, "cu4");
  G4LogicalVolume* log_gt1  = new G4LogicalVolume( sol_gt1 ,   g10_mat, "gt1");
  G4LogicalVolume* log_gt2  = new G4LogicalVolume( sol_gt2 ,   g10_mat, "gt2");
  G4LogicalVolume* log_gt3  = new G4LogicalVolume( sol_gt3 ,   g10_mat, "gt3");
  G4LogicalVolume* log_gt4  = new G4LogicalVolume( sol_gt4 ,   g10_mat, "gt4");
  G4LogicalVolume* log_ai1  = new G4LogicalVolume( sol_ai1 ,   air_mat, "ai1");
  G4LogicalVolume* log_ai2  = new G4LogicalVolume( sol_ai2 ,   air_mat, "ai2");
  G4LogicalVolume* log_Ar   = new G4LogicalVolume( sol_Ar  ,     ArGas,  "Ar");

  G4double cga   =       cu_Z+g10_Z+air_Z;
  G4double wcga  = w_Z + cu_Z+g10_Z+air_Z;
  G4double edge1 = w_Z + 2.*cu_Z+2.*g10_Z+air_Z;

  G4ThreeVector pos_Sr  ;  pos_Sr .set(0,0, -sr_Z*0.5);
  G4ThreeVector pos_st1 ;  pos_st1.set(0,0, -sr_Z*0.5);
  G4ThreeVector pos_st2 ;  pos_st2.set(0,0, -sr_Z-steel2_Z*0.5);
  G4ThreeVector pos_pl1 ;  pos_pl1.set(0,0, -plexi1_Z*0.5);
  G4ThreeVector pos_pl2 ;  pos_pl2.set(0,0, -plexi1_Z-plexi2_Z*0.5);
  G4ThreeVector pos_pb1 ;  pos_pb1.set(0,0, -pb1_Z*0.5);
  G4ThreeVector pos_pb2 ;  pos_pb2.set(0,0, -pb1_Z-pb2_Z*0.5);
  G4ThreeVector pos_w   ;  pos_w  .set(0,0, w_Z*0.5);
  G4ThreeVector pos_cu1 ;  pos_cu1.set(0,0, w_Z + cu_Z*0.5);
  G4ThreeVector pos_gt1 ;  pos_gt1.set(0,0, w_Z+cu_Z+g10_Z*0.5);
  G4ThreeVector pos_ai1 ;  pos_ai1.set(0,0, wcga - air_Z*0.5);
  G4ThreeVector pos_gt2 ;  pos_gt2.set(0,0, wcga + g10_Z*0.5);
  G4ThreeVector pos_cu2 ;  pos_cu2.set(0,0, wcga + g10_Z + cu_Z*0.5);
  G4ThreeVector pos_Ar  ;  pos_Ar .set(0,0, edge1 + ar_Z*0.5);
  G4ThreeVector pos_cu3 ;  pos_cu3.set(0,0, edge1 + ar_Z + cu_Z*0.5);
  G4ThreeVector pos_gt3 ;  pos_gt3.set(0,0, edge1 + ar_Z + cu_Z + g10_Z*0.5);
  G4ThreeVector pos_ai2 ;  pos_ai2.set(0,0, edge1 + ar_Z + cga - air_Z*0.5);
  G4ThreeVector pos_gt4 ;  pos_gt4.set(0,0, edge1 + ar_Z + cga + g10_Z*0.5);
  G4ThreeVector pos_cu4 ;  pos_cu4.set(0,0, edge1 + ar_Z + cga + g10_Z + cu_Z*0.5);


  G4VPhysicalVolume* physWorld =
     new G4PVPlacement(0, world_pos, logicWorld , "World" ,           0, false, 0, ckOv );
     new G4PVPlacement(0, pos_Sr   , log_Sr     , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_st1  , log_st1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_st2  , log_st2    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_pl1  , log_pl1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_pl2  , log_pl2    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_pb1  , log_pb1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_pb2  , log_pb2    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_w    , log_w      , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_cu1  , log_cu1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_cu2  , log_cu2    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_cu3  , log_cu3    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_cu4  , log_cu4    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_gt1  , log_gt1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_gt2  , log_gt2    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_gt3  , log_gt3    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_gt4  , log_gt4    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_ai1  , log_ai1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_ai2  , log_ai1    , ""   , logicWorld,  false, 0, ckOv );
     new G4PVPlacement(0, pos_Ar   , log_Ar     , ""   , logicWorld,  false, 0, ckOv );

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

  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Shape 1
  //  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos1 = G4ThreeVector(0, 2*cm, -7*cm);
        
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  G4double shape1_hz = 3.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Shape 2
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);

  // Trapezoid shape       
  G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
  G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
  G4double shape2_dz  = 6*cm;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
