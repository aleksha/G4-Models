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
// $Id: Sr90TESTActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file Sr90TESTActionInitialization.cc
/// \brief Implementation of the Sr90TESTActionInitialization class

#include "Sr90TESTActionInitialization.hh"
#include "Sr90TESTPrimaryGeneratorAction.hh"
#include "Sr90TESTRunAction.hh"
#include "Sr90TESTEventAction.hh"
#include "Sr90TESTSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTActionInitialization::Sr90TESTActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Sr90TESTActionInitialization::~Sr90TESTActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Sr90TESTActionInitialization::BuildForMaster() const
{
  Sr90TESTRunAction* runAction = new Sr90TESTRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Sr90TESTActionInitialization::Build() const
{
  SetUserAction(new Sr90TESTPrimaryGeneratorAction);

  Sr90TESTRunAction* runAction = new Sr90TESTRunAction;
  SetUserAction(runAction);
  
  Sr90TESTEventAction* eventAction = new Sr90TESTEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new Sr90TESTSteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
