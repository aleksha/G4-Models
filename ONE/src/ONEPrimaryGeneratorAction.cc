#include "ONEPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
//------------------------------------------------------------------------------
ONEPrimaryGeneratorAction::ONEPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(0.7*MeV);
}
//------------------------------------------------------------------------------
ONEPrimaryGeneratorAction::~ONEPrimaryGeneratorAction(){ delete fParticleGun; }
//------------------------------------------------------------------------------
void ONEPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  fParticleGun->SetParticlePosition( G4ThreeVector(0,0,0) );
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

