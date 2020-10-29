#ifndef RFZPrimaryGeneratorAction_h
#define RFZPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class PrimaryGenerator;

/// The primary generator action class with particle gun.

class RFZPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    RFZPrimaryGeneratorAction();
    virtual ~RFZPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

  private:
    PrimaryGenerator* fPrimaryGenerator; // pointer a to object of primary gen class

};
//------------------------------------------------------------------------------
#endif
