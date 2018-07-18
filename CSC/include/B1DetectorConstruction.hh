#ifndef CSCDetectorConstruction_h
#define CSCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class CSCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    CSCDetectorConstruction();
    virtual ~CSCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetLV0() const { return fLV0; }
    G4LogicalVolume* GetLV1() const { return fLV1; }
    G4LogicalVolume* GetLV2() const { return fLV2; }
    G4LogicalVolume* GetLV3() const { return fLV3; }
    G4LogicalVolume* GetLV4() const { return fLV4; }
    G4LogicalVolume* GetLV5() const { return fLV5; }
    G4LogicalVolume* GetLV6() const { return fLV6; }
    G4LogicalVolume* GetLV7() const { return fLV7; }
    G4LogicalVolume* GetLV8() const { return fLV8; }
    G4LogicalVolume* GetLV9() const { return fLV9; }

  protected:
    G4LogicalVolume*  fLV0;
    G4LogicalVolume*  fLV1;
    G4LogicalVolume*  fLV2;
    G4LogicalVolume*  fLV3;
    G4LogicalVolume*  fLV4;
    G4LogicalVolume*  fLV5;
    G4LogicalVolume*  fLV6;
    G4LogicalVolume*  fLV7;
    G4LogicalVolume*  fLV8;
    G4LogicalVolume*  fLV9;
};

#endif

