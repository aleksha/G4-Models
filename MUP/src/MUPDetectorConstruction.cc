//------------------------------------------------------------------------------
#include "MUPDetectorConstruction.hh"
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
MUPDetectorConstruction::MUPDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0)
{ }
//------------------------------------------------------------------------------
MUPDetectorConstruction::~MUPDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* MUPDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  //G4double z, a, density;
  //G4double temperature, pressure;
  //G4int ncomponents, natoms;
  //G4double fractionmass;

  // Elements
  //G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  //#G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  //G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);

  //G4Material* scinc = new G4Material(name="scinc", density = 1.032*g/cm3, ncomponents=2);
  //scinc->AddElement(C, natoms=9);
  //scinc->AddElement(H, natoms=10);

  //Gases
  //G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  //CH4Gas->AddElement(H,4);
  //CH4Gas->AddElement(C,1);
  //G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
  //G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 32.2354*kg/m3, ncomponents=2);
  //ArCH4->AddMaterial (  ArGas,  fractionmass = 0.978811);
  //ArCH4->AddMaterial( CH4Gas,  fractionmass = 0.021189);
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


//------------------------------------------
//   World
//------------------------------------------
  G4double w_xy =   220.0*mm;
  G4double w_z  = 11000.0*mm;

  //G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* w_mat = nist->FindOrBuildMaterial("G4_He");

//------------------------------------------
//   Si layers
//------------------------------------------

  // Geometrical parameters of Si layers
  G4double l_xy  =  200.000*mm;
  G4double lSi_z =    0.250*mm;
  // z-pozitiion of Si layers
  G4double l00_z = -5450.000*mm + 0.5 * lSi_z;
  G4double l01_z =  -450.000*mm + 0.5 * lSi_z;
  G4double l02_z =   450.000*mm - 0.5 * lSi_z;
  G4double l03_z =  5450.000*mm - 0.5 * lSi_z;

  //G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* SiSolid = nist->FindOrBuildMaterial("G4_Si");
  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV00 =  new G4Box("LV00", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV01 =  new G4Box("LV01", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV02 =  new G4Box("LV02", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV03 =  new G4Box("LV03", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);

  //G4Material* l00_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l01_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l02_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l03_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00, SiSolid, "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01, SiSolid, "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02, SiSolid, "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03, SiSolid, "LV03");

  G4ThreeVector l00_pos; l00_pos.set( 0, 0, l00_z );
  G4ThreeVector l01_pos; l01_pos.set( 0, 0, l01_z );
  G4ThreeVector l02_pos; l02_pos.set( 0, 0, l02_z );
  G4ThreeVector l03_pos; l03_pos.set( 0, 0, l03_z );

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0, l00_pos, logicLV00, "LV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV01", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "LV02", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "LV03", logicWorld, false, 0, checkOverlaps);

  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;

  return physWorld;
}
//------------------------------------------------------------------------------
