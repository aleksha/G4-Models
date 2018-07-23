//
// ********************************************************************
// * Monte-Carlo for TPC at elactron beam                             *
// *                                                                  *
// * Author : Alexey Dzyuba / PNPI Gatchina                           *
// * E-Mail : a.dzyuba  @  gmail.com                                  *
// * Date   : 2017-09-29                                              *
// *                                                                  *
// * The program is based on the exampleTPC                            *
// *                                                                  *
// *                                                                  *
// *                                                                  *
// ********************************************************************


#include "TPCDetectorConstruction.hh"
#include "TPCActionInitialization.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"


int main(int argc,char** argv)
{

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new TPCDetectorConstruction());

  // Physics list
  //G4VModularPhysicsList* physicsList = new QBBC;
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new TPCActionInitialization());

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }


  delete runManager;
}
//-----------------------------------------------------------------------------
