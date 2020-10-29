#include "RFZPrimaryGeneratorAction.hh"

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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

  private:
    G4double fXpos, fYpos, fZpos; //solid angle
    G4double fTp, fTHETAp, fPHIp; //
    G4double fTe, fTHETAe, fPHIe; //
    std::ofstream myGEN   ;
    std::ifstream myESEPP ;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{
  myGEN  .open( "gen.data"   , std::ios::trunc );
  myESEPP.open( "esepp.data" , std::ios::in    );
}

PrimaryGenerator::~PrimaryGenerator()
{
 myGEN  .close();
 myESEPP.close();
}

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

  fXpos = 0.*mm;  fYpos = 0.*mm;  fZpos = 10.*mm;
  if( true ){
//    if(G4UniformRand()>0.5){ fZpos = (60*G4UniformRand() + 400.-10.-60.)*mm;}
//    else{                    fZpos = (60*G4UniformRand() + 10.)*mm;         }
    fZpos = (380*G4UniformRand() + 10.)*mm;
    fXpos = (G4UniformRand() - 0.5)*0.1*mm;
    fYpos = (G4UniformRand() - 0.5)*0.1*mm;
    while( fXpos*fXpos + fYpos*fYpos > 0.1*0.1 ){
      fXpos = (G4UniformRand() - 0.5)*0.1*mm;
      fYpos = (G4UniformRand() - 0.5)*0.1*mm;
    }
  }

  myESEPP >> fTHETAp >> fPHIp >> fTp >> fTHETAe >> fPHIe >> fTe;

  G4ParticleDefinition* particleDefP = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  G4ParticleDefinition* particleDefE = G4ParticleTable::GetParticleTable()->FindParticle("e-");

  G4PrimaryParticle* particle1;
  G4PrimaryParticle* particle2;

  particle1 = new G4PrimaryParticle(particleDefP);
  particle2 = new G4PrimaryParticle(particleDefE);


  G4ThreeVector positionB( fXpos, fYpos, fZpos );
  G4ThreeVector dir_p( sin(fTHETAp)*cos(fPHIp), sin(fTHETAp)*sin(fPHIp), cos(fTHETAp) );
  G4ThreeVector dir_e( sin(fTHETAe)*cos(fPHIe), sin(fTHETAe)*sin(fPHIe), cos(fTHETAe) );

  particle1->SetKineticEnergy(fTp);
  particle2->SetTotalEnergy(fTe);

  particle1->SetMomentumDirection( dir_p );
  particle2->SetMomentumDirection( dir_e );

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);

  vertexB->SetPrimary( particle1 );
  vertexB->SetPrimary( particle2 );

  event->AddPrimaryVertex( vertexB );

  myGEN << fTHETAp << " " << fPHIp << " " << fTp   << " "  ;
  myGEN << fTHETAe << " " << fPHIe << " " << fTe   << " "  ;
  myGEN << fXpos   << " " << fYpos << " " << fZpos << "\n" ;

}

//------------------------------------------------------------------------------
RFZPrimaryGeneratorAction::RFZPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fPrimaryGenerator(0)
{
  fPrimaryGenerator = new PrimaryGenerator();
}
//------------------------------------------------------------------------------
RFZPrimaryGeneratorAction::~RFZPrimaryGeneratorAction(){ delete fPrimaryGenerator; }
//------------------------------------------------------------------------------
void RFZPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

