#ifndef TPCPrimaryGeneratorAction_h
#define TPCPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class PrimaryGenerator;

class TPCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TPCPrimaryGeneratorAction();    
    virtual ~TPCPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         
  
  private:
    PrimaryGenerator*  fPrimaryGenerator; // pointer a to G4 gun class
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
