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
// $Id: TPCSteppingAction.hh 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file TPCSteppingAction.hh
/// \brief Definition of the TPCSteppingAction class

#ifndef TPCSteppingAction_h
#define TPCSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct sa_Config {
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



class TPCEventAction;
class G4LogicalVolume;

/// Stepping action class
///

class TPCSteppingAction : public G4UserSteppingAction
{
  public:
    TPCSteppingAction(TPCEventAction* eventAction);
    virtual ~TPCSteppingAction();

    sa_Config loadConfig();
    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    TPCEventAction*  fEventAction;

    std::ofstream myMWPCp    ;
    std::ofstream myTPCp     ;
    std::ofstream myMWPC     ;
    std::ofstream myTPC      ;
    std::ofstream myGen      ;
    std::ofstream myRest     ;
    std::ofstream myEnd      ;
    std::ifstream configFile ;

    int SimMode              ;
    int TrackProtons         ;
    G4LogicalVolume*  fTPC   ;
    G4LogicalVolume*  fSci   ;
    G4LogicalVolume*  fShi   ;
    G4LogicalVolume*  fFln   ;
    G4LogicalVolume*  fEnd   ;

    sa_Config config;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
