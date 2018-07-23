//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: TPCDetectorConstruction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file TPCDetectorConstruction.hh
/// \brief Definition of the TPCDetectorConstruction class

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

