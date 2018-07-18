//------------------------------------------------------------------------------
#include "CSCDetectorConstruction.hh"
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
CSCDetectorConstruction::CSCDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV0(0), fLV1(0), fLV2(0), fLV3(0), fLV4(0),
  fLV5(0), fLV6(0), fLV7(0), fLV8(0), fLV9(0)
{ }
//------------------------------------------------------------------------------
CSCDetectorConstruction::~CSCDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* CSCDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();




  G4String name;
  G4double z, a, density;
  //G4double temperature, pressure;
  G4int ncomponents;//, natoms;
  G4double fractionmass;

  // Elements
  G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  //G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);

  //G4Material* SciSolid = new G4Material(name="SciSolid", density = 1.032*g/cm3, ncomponents=2);
  //SciSolid->AddElement(C, natoms=9);
  //SciSolid->AddElement(H, natoms=10);

  //Gases
  G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  CH4Gas->AddElement(H,4);
  CH4Gas->AddElement(C,1);
  G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
  G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 32.2354*kg/m3, ncomponents=2);
  ArCH4->AddMaterial (  ArGas,  fractionmass = 0.978811);
  ArCH4->AddMaterial( CH4Gas,  fractionmass = 0.021189);
  //G4Material *H2Gas   = new G4Material("H2Gas"  ,  1,  1.008  *g/mole,  1.6347*kg/m3 );
  //Solids
  //G4Material *BeSolid = new G4Material("BeSolid",  4,  9.01218  *g/mole,  1.848 * g/cm3 );
  //G4Material *SiSolid = new G4Material("SiSolid", 14, 28.0855   *g/mole,  2.33  * g/cm3 );
  //G4Material *AlSolid = new G4Material("AlSolid", 13, 26.9815385*g/mole,  2.700 * g/cm3 );
  //G4Material *CuSolid = new G4Material("CuSolid", 29, 63.543    *g/mole,  8.96  * g/cm3 );
  //G4Material* Mylar = new G4Material(name="Mylar", 1.39*g/cm3, 3);
  //Mylar->AddElement(O,2);
  //Mylar->AddElement(C,5);
  //Mylar->AddElement(H,4);

  //G4Material* CarbonFiber = new G4Material(name="CarbonFiber",0.145*g/cm3, 1);
  //CarbonFiber->AddElement(C,1);





  // Layer (LV) geometrical parameters
  G4double l_xy = 999.000*mm;
  G4double l0_z =  10.000*mm;
  G4double l1_z =  10.000*mm;
  G4double l2_z =  10.000*mm;
  G4double l3_z =  10.000*mm;
  G4double l4_z =  10.000*mm;
  G4double l5_z =  22.000*mm;
  G4double l6_z =   3.000*mm;
  G4double l7_z =   3.000*mm;
  G4double l8_z =   0.001*mm;
  G4double l9_z =   0.001*mm;

  // World
  G4double w_xy = 1000.0*mm;
  G4double w_z  = 1000.0*mm;
  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV0 =  new G4Box("LV0", 0.5*l_xy, 0.5*l_xy, 0.5*l0_z);
  G4Box* solidLV1 =  new G4Box("LV1", 0.5*l_xy, 0.5*l_xy, 0.5*l1_z);
  G4Box* solidLV2 =  new G4Box("LV2", 0.5*l_xy, 0.5*l_xy, 0.5*l2_z);
  G4Box* solidLV3 =  new G4Box("LV3", 0.5*l_xy, 0.5*l_xy, 0.5*l3_z);
  G4Box* solidLV4 =  new G4Box("LV4", 0.5*l_xy, 0.5*l_xy, 0.5*l4_z);
  G4Box* solidLV5 =  new G4Box("LV5", 0.5*l_xy, 0.5*l_xy, 0.5*l5_z);
  G4Box* solidLV6 =  new G4Box("LV6", 0.5*l_xy, 0.5*l_xy, 0.5*l6_z);
  G4Box* solidLV7 =  new G4Box("LV7", 0.5*l_xy, 0.5*l_xy, 0.5*l7_z);
  G4Box* solidLV8 =  new G4Box("LV8", 0.5*l_xy, 0.5*l_xy, 0.5*l8_z);
  G4Box* solidLV9 =  new G4Box("LV9", 0.5*l_xy, 0.5*l_xy, 0.5*l9_z);

  //G4Material* l0_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l1_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l2_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l3_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l4_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l5_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l6_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l7_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* l8_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* l9_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume* logicLV0 = new G4LogicalVolume(solidLV0, steel , "LV0");
  G4LogicalVolume* logicLV1 = new G4LogicalVolume(solidLV1, steel , "LV1");
  G4LogicalVolume* logicLV2 = new G4LogicalVolume(solidLV2, steel , "LV2");
  G4LogicalVolume* logicLV3 = new G4LogicalVolume(solidLV3, steel , "LV3");
  G4LogicalVolume* logicLV4 = new G4LogicalVolume(solidLV4, steel , "LV4");
  G4LogicalVolume* logicLV5 = new G4LogicalVolume(solidLV5, ArCH4 , "LV5");
  G4LogicalVolume* logicLV6 = new G4LogicalVolume(solidLV6, ArCH4 , "LV6");
  G4LogicalVolume* logicLV7 = new G4LogicalVolume(solidLV7, ArCH4 , "LV7");
  G4LogicalVolume* logicLV8 = new G4LogicalVolume(solidLV8, l8_mat, "LV8");
  G4LogicalVolume* logicLV9 = new G4LogicalVolume(solidLV9, l9_mat, "LV9");


  G4double shft = 10.*mm;
  G4ThreeVector l0_pos; l0_pos.set(0,0,0.5*l0_z-0.5*w_z+shft);
  G4ThreeVector l1_pos; l1_pos.set(0,0,l0_z+0.5*l1_z-0.5*w_z+shft);
  G4ThreeVector l2_pos; l2_pos.set(0,0,l0_z+l1_z+0.5*l2_z-0.5*w_z+shft);
  G4ThreeVector l3_pos; l3_pos.set(0,0,l0_z+l1_z+l2_z+0.5*l3_z-0.5*w_z+shft);
  G4ThreeVector l4_pos; l4_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+0.5*l4_z-0.5*w_z+shft);
  G4ThreeVector l5_pos; l5_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+l4_z+0.5*l5_z-0.5*w_z+shft);
  G4ThreeVector l6_pos; l6_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+l4_z+l5_z+0.5*l6_z-0.5*w_z+shft);
  G4ThreeVector l7_pos; l7_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+l4_z+l5_z+l6_z+0.5*l7_z-0.5*w_z+shft);
  G4ThreeVector l8_pos; l8_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+l4_z+l5_z+l6_z+l7_z+0.5*l8_z-0.5*w_z+shft);
  G4ThreeVector l9_pos; l9_pos.set(0,0,l0_z+l1_z+l2_z+l3_z+l4_z+l5_z+l6_z+l7_z+l8_z+0.5*l9_z-0.5*w_z+shft);

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0, l0_pos, logicLV0, "LV0", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l1_pos, logicLV1, "LV1", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l2_pos, logicLV2, "LV2", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l3_pos, logicLV3, "LV3", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l4_pos, logicLV4, "LV4", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l5_pos, logicLV5, "LV5", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l6_pos, logicLV6, "LV6", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l7_pos, logicLV7, "LV7", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l8_pos, logicLV8, "LV8", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l9_pos, logicLV9, "LV9", logicWorld, false, 0, checkOverlaps);

  fLV0 = logicLV0;
  fLV1 = logicLV1;
  fLV2 = logicLV2;
  fLV3 = logicLV3;
  fLV4 = logicLV4;
  fLV5 = logicLV5;
  fLV6 = logicLV6;
  fLV7 = logicLV7;
  fLV8 = logicLV8;
  fLV9 = logicLV9;

  return physWorld;
}
//------------------------------------------------------------------------------
