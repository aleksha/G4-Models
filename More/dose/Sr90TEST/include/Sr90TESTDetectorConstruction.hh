
#ifndef Sr90TESTDetectorConstruction_h
#define Sr90TESTDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class Sr90TESTDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    Sr90TESTDetectorConstruction();
    virtual ~Sr90TESTDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

