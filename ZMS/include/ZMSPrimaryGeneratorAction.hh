#ifndef ZMSPrimaryGeneratorAction_h
#define ZMSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class G4ParticleGun;
class G4Event;
//class G4Box;

/// The primary generator action class with particle gun.

class ZMSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ZMSPrimaryGeneratorAction();
    virtual ~ZMSPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    std::ofstream myGEN;
    std::ifstream myESEPP;
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    double fAngle  ;
    double ang     ;
    double fEnergy ;
    double fZpos   ;
    double fTHETA  ; // unit vector fo momentum direction
    double fPHI    ;
//    G4Box* fEnvelopeBox;
};
//------------------------------------------------------------------------------
#endif
