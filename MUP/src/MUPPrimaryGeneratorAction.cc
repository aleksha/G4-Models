#include "MUPPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4VPrimaryGenerator.hh"

//==============================================================================
// HERE IS PRIMARY GENERATOR CLASS FIRST
//==============================================================================


class PrimaryGenerator : public G4VPrimaryGenerator
{
  public:
    PrimaryGenerator();
   ~PrimaryGenerator();

  public:
    virtual void GeneratePrimaryVertex(G4Event*);

//  private:
//    G4double fCosAlphaMin, fCosAlphaMax;      //solid angle

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{ }

PrimaryGenerator::~PrimaryGenerator()
{ }

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

  G4ParticleDefinition* particleDefMu = G4ParticleTable::GetParticleTable()->FindParticle("mu+");

  G4PrimaryParticle* particle1;
  G4PrimaryParticle* particle2;

  particle1 = new G4PrimaryParticle(particleDefMu);
  particle2 = new G4PrimaryParticle(particleDefMu);

  G4double p_mu = 100.*GeV;
  G4double pos  = 20.*mm;
  double theta = 0.00033;


  G4ThreeVector positionB( 0, 0, pos );

  particle1->SetMomentum( 0,          0, -p_mu );
  particle2->SetMomentum( 0, theta*p_mu,  p_mu );

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);

  event->AddPrimaryVertex(vertexB);

}

//------------------------------------------------------------------------------
MUPPrimaryGeneratorAction::MUPPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  PrimaryGenerator(0)
{
  fPrimaryGenerator = new PrimaryGenerator();
}
//------------------------------------------------------------------------------
MUPPrimaryGeneratorAction::~MUPPrimaryGeneratorAction(){ delete fPrimaryGenerator; }
//------------------------------------------------------------------------------
void MUPPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

