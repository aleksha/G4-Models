
#ifndef TPCDetectorConstruction_h
#define TPCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct dc_Config {
  int    N_ev         ;
  double E_e          ;
  double Tp           ;
  double Pressure     ;
  double zTPC         ;
  double lTPC         ;
  int    MatMode      ;
  int    BeWindow     ;
  int    BeamSmearing ;
  double BeamTheta    ;
  double BeamPos      ;
};

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class TPCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    TPCDetectorConstruction();
    virtual ~TPCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    dc_Config loadConfig();
    
    G4LogicalVolume* GetTPC()     const { return fTPC; }
    G4LogicalVolume* GetSci()     const { return fSci; }
    G4LogicalVolume* GetShi()     const { return fShi; }
    G4LogicalVolume* GetFln()     const { return fFln; }
    G4LogicalVolume* GetEnd()     const { return fEnd; }

  protected:
    G4LogicalVolume*  fTPC   ;
    G4LogicalVolume*  fSci   ;
    G4LogicalVolume*  fShi   ;
    G4LogicalVolume*  fFln   ;
    G4LogicalVolume*  fEnd   ;
    
    std::ifstream zTPCFile;
    
    int SimMode;
    int MatMode;
    
    double zTPC     ;
    double posTPC   ;
    double lengthTPC;
    double BeWindow ;
    double ArGap1   ;
    double ArGap2   ;
    double MWPCGap  ;
    
    dc_Config config;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

