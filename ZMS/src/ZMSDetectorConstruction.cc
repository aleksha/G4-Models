//------------------------------------------------------------------------------
#include "ZMSDetectorConstruction.hh"
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
ZMSDetectorConstruction::ZMSDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0), fLV04(0),
  fLV05(0), fLV06(0), fLV07(0), fLV08(0), fLV09(0),
  fLV10(0), fLV11(0), fLV12(0), fLV13(0), fLV14(0),
  fLV15(0), fLV16(0)
{ }
//------------------------------------------------------------------------------
ZMSDetectorConstruction::~ZMSDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* ZMSDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();




  G4String name;
  //G4double z, a, density;
  //G4double temperature, pressure;
  //G4int ncomponents, natoms;
  //G4double fractionmass;

  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* u_mat = nist->FindOrBuildMaterial("G4_Galactic");
 // G4Material* d_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* t_mat= nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  //G4Material* t_mat= nist->FindOrBuildMaterial("G4_Be");

  G4Material *h_mat  = new G4Material("h_mat", 1, 1.008*g/mole, 1.6347*kg/m3 ); // 20 atm H2 = 1.6347*kg/m3

  // World
  G4double w_xy = 1000.0*mm;
  G4double w_z  = 1000.0*mm;

  // Layer (LV) geometrical parameters
  G4double l_xy = 999.000*mm;
  G4double hyd_layer = 400.0*mm;
  G4double dum_layer = 0.001*mm;

  G4double l00_z = hyd_layer;

  G4double l01_z = dum_layer;
  G4double l02_z = dum_layer;
  G4double l03_z = dum_layer;
  G4double l04_z = dum_layer;
  G4double l05_z = dum_layer;
  G4double l06_z = dum_layer;
  G4double l07_z = dum_layer;
  G4double l08_z = dum_layer;
  G4double l09_z = dum_layer;
  G4double l10_z = dum_layer;
  G4double l11_z = dum_layer;
  G4double l12_z = dum_layer;
  G4double l13_z = dum_layer;
  G4double l14_z = dum_layer;
  G4double l15_z = dum_layer;
  G4double l16_z = dum_layer;

  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV00 =  new G4Box("LV00", 0.5*l_xy, 0.5*l_xy, 0.5*l00_z);
  G4Box* solidLV01 =  new G4Box("LV01", 0.5*l_xy, 0.5*l_xy, 0.5*l01_z);
  G4Box* solidLV02 =  new G4Box("LV02", 0.5*l_xy, 0.5*l_xy, 0.5*l02_z);
  G4Box* solidLV03 =  new G4Box("LV03", 0.5*l_xy, 0.5*l_xy, 0.5*l03_z);
  G4Box* solidLV04 =  new G4Box("LV04", 0.5*l_xy, 0.5*l_xy, 0.5*l04_z);
  G4Box* solidLV05 =  new G4Box("LV05", 0.5*l_xy, 0.5*l_xy, 0.5*l05_z);
  G4Box* solidLV06 =  new G4Box("LV06", 0.5*l_xy, 0.5*l_xy, 0.5*l06_z);
  G4Box* solidLV07 =  new G4Box("LV07", 0.5*l_xy, 0.5*l_xy, 0.5*l07_z);
  G4Box* solidLV08 =  new G4Box("LV08", 0.5*l_xy, 0.5*l_xy, 0.5*l08_z);
  G4Box* solidLV09 =  new G4Box("LV09", 0.5*l_xy, 0.5*l_xy, 0.5*l09_z);
  G4Box* solidLV10 =  new G4Box("LV10", 0.5*l_xy, 0.5*l_xy, 0.5*l10_z);
  G4Box* solidLV11 =  new G4Box("LV11", 0.5*l_xy, 0.5*l_xy, 0.5*l11_z);
  G4Box* solidLV12 =  new G4Box("LV12", 0.5*l_xy, 0.5*l_xy, 0.5*l12_z);
  G4Box* solidLV13 =  new G4Box("LV13", 0.5*l_xy, 0.5*l_xy, 0.5*l13_z);
  G4Box* solidLV14 =  new G4Box("LV14", 0.5*l_xy, 0.5*l_xy, 0.5*l14_z);
  G4Box* solidLV15 =  new G4Box("LV15", 0.5*l_xy, 0.5*l_xy, 0.5*l15_z);
  G4Box* solidLV16 =  new G4Box("LV16", 0.5*l_xy, 0.5*l_xy, 0.5*l16_z);

  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00, h_mat , "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01, u_mat , "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02, u_mat , "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03, u_mat , "LV03");
  G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04, u_mat , "LV04");
  G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05, u_mat , "LV05");
  G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06, u_mat , "LV06");
  G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07, u_mat , "LV07");
  G4LogicalVolume* logicLV08 = new G4LogicalVolume(solidLV08, u_mat , "LV08");
  G4LogicalVolume* logicLV09 = new G4LogicalVolume(solidLV09, u_mat , "LV09");
  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10, u_mat , "LV10");
  G4LogicalVolume* logicLV11 = new G4LogicalVolume(solidLV11, u_mat , "LV11");
  G4LogicalVolume* logicLV12 = new G4LogicalVolume(solidLV12, u_mat , "LV12");
  G4LogicalVolume* logicLV13 = new G4LogicalVolume(solidLV13, u_mat , "LV13");
  G4LogicalVolume* logicLV14 = new G4LogicalVolume(solidLV14, u_mat , "LV14");
  G4LogicalVolume* logicLV15 = new G4LogicalVolume(solidLV15, u_mat , "LV15");
  G4LogicalVolume* logicLV16 = new G4LogicalVolume(solidLV16, u_mat , "LV16");



  G4ThreeVector l00_pos; l00_pos.set(0,0,0.5*hyd_layer);

  G4ThreeVector l01_pos; l01_pos.set(0,0,0.5*w_z - 15.5*dum_layer);
  G4ThreeVector l02_pos; l02_pos.set(0,0,0.5*w_z - 14.5*dum_layer);
  G4ThreeVector l03_pos; l03_pos.set(0,0,0.5*w_z - 13.5*dum_layer);
  G4ThreeVector l04_pos; l04_pos.set(0,0,0.5*w_z - 12.5*dum_layer);
  G4ThreeVector l05_pos; l05_pos.set(0,0,0.5*w_z - 11.5*dum_layer);
  G4ThreeVector l06_pos; l06_pos.set(0,0,0.5*w_z - 10.5*dum_layer);
  G4ThreeVector l07_pos; l07_pos.set(0,0,0.5*w_z -  9.5*dum_layer);
  G4ThreeVector l08_pos; l08_pos.set(0,0,0.5*w_z -  8.5*dum_layer);
  G4ThreeVector l09_pos; l09_pos.set(0,0,0.5*w_z -  7.5*dum_layer);
  G4ThreeVector l10_pos; l10_pos.set(0,0,0.5*w_z -  6.5*dum_layer);
  G4ThreeVector l11_pos; l11_pos.set(0,0,0.5*w_z -  5.5*dum_layer);
  G4ThreeVector l12_pos; l12_pos.set(0,0,0.5*w_z -  4.5*dum_layer);
  G4ThreeVector l13_pos; l13_pos.set(0,0,0.5*w_z -  3.5*dum_layer);
  G4ThreeVector l14_pos; l14_pos.set(0,0,0.5*w_z -  2.5*dum_layer);
  G4ThreeVector l15_pos; l15_pos.set(0,0,0.5*w_z -  1.5*dum_layer);
  G4ThreeVector l16_pos; l16_pos.set(0,0,0.5*w_z -  0.5*dum_layer);


  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0, l00_pos, logicLV00, "LV10", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV11", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "LV12", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "LV13", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l04_pos, logicLV04, "LV14", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l05_pos, logicLV05, "LV15", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l06_pos, logicLV06, "LV16", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l07_pos, logicLV07, "LV17", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l08_pos, logicLV08, "LV18", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l09_pos, logicLV09, "LV19", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l10_pos, logicLV10, "LV10", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l11_pos, logicLV11, "LV11", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l12_pos, logicLV12, "LV12", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l13_pos, logicLV13, "LV13", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l14_pos, logicLV14, "LV14", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l15_pos, logicLV15, "LV15", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l16_pos, logicLV16, "LV16", logicWorld, false, 0, checkOverlaps);

  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;
  fLV04 = logicLV04;
  fLV05 = logicLV05;
  fLV06 = logicLV06;
  fLV07 = logicLV07;
  fLV08 = logicLV08;
  fLV09 = logicLV09;
  fLV10 = logicLV10;
  fLV11 = logicLV11;
  fLV12 = logicLV12;
  fLV13 = logicLV13;
  fLV14 = logicLV14;
  fLV15 = logicLV15;
  fLV16 = logicLV16;

  return physWorld;
}
//------------------------------------------------------------------------------
