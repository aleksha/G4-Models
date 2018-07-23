#include "TPCActionInitialization.hh"
#include "TPCPrimaryGeneratorAction.hh"
#include "TPCRunAction.hh"
#include "TPCEventAction.hh"
#include "TPCSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCActionInitialization::TPCActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCActionInitialization::~TPCActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCActionInitialization::BuildForMaster() const
{
  TPCRunAction* runAction = new TPCRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCActionInitialization::Build() const
{
  SetUserAction(new TPCPrimaryGeneratorAction);

  TPCRunAction* runAction = new TPCRunAction;
  SetUserAction(runAction);
  
  TPCEventAction* eventAction = new TPCEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new TPCSteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
