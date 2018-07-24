#ifndef Sr90TESTPrimaryGeneratorAction_h
#define Sr90TESTPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class PrimaryGenerator;

class Sr90TESTPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TPCPrimaryGeneratorAction();    
    virtual ~TPCPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

  private:
    PrimaryGenerator*  fPrimaryGenerator; 
};

#endif
