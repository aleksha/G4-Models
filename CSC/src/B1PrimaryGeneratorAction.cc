#include "B1PrimaryGeneratorAction.hh"
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
B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
//  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu+");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
//  fParticleGun->SetParticleEnergy(1000.*MeV);
  fParticleGun->SetParticleEnergy(55.*MeV);
}
//------------------------------------------------------------------------------
B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction(){ delete fParticleGun; }
//------------------------------------------------------------------------------
void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  fParticleGun->SetParticlePosition( G4ThreeVector(0,0,-499.5*mm) );
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

