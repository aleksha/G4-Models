#include "ZMSPrimaryGeneratorAction.hh"
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
ZMSPrimaryGeneratorAction::ZMSPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{

  fAngle = 5;
  fEnergy= 5;
  fZpos  = 200.;
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);

  myGEN  .open( "gen.data"   , std::ios::trunc );
  myESEPP.open( "esepp.data" , std::ios::in    );
}
//------------------------------------------------------------------------------
ZMSPrimaryGeneratorAction::~ZMSPrimaryGeneratorAction(){
  delete fParticleGun;
  myGEN.close();
  myESEPP.close();
}
//------------------------------------------------------------------------------
void ZMSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event

  myESEPP >> fTHETA >> fPHI >> fEnergy;

  fAngle  = (3.14159265*0.5-fTHETA)*180./3.14159265 ;
//  fEnergy = 2.0  + G4UniformRand()* 8. ;
//  fZpos   = 190. + G4UniformRand()*20. ;

//  fAngle  =   0. ;
//  fAngle  =   2.5 ;
//  fAngle  =   5.0 ;
//  fEnergy =   5. ;
  fZpos   = 200. ;

  ang = fAngle*3.14159265/180.;

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,cos(ang),sin(ang)));
  fParticleGun->SetParticleEnergy(fEnergy*MeV);
  fParticleGun->SetParticlePosition( G4ThreeVector(0, 0, fZpos*mm) );
  fParticleGun->GeneratePrimaryVertex(anEvent);
  myGEN << fAngle << " " << fEnergy << " " << fZpos << G4endl;
}
//------------------------------------------------------------------------------

