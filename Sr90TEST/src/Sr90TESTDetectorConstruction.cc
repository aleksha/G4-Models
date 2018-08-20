#include "Sr90TESTDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
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

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
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
  G4Material* G10 = new G4Material("G10", density=1.700*g/cm3, ncomponents=4);
  G10->AddElement(Si,natoms=1); G10->AddElement(O,natoms=2);
  G10->AddElement(C ,natoms=3); G10->AddElement(H,natoms=3);

  G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 1.784 *kg/m3 );

  G4double sr_XY = 2*mm, sr_Z = 2*mm;
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

  G4double chamber_R  = 200.0*mm;


  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
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
