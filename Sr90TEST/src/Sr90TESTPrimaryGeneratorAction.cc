
#include "Sr90TESTPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

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
    std::ifstream in_file ;
    double Egamma = 2.2792  ;
    double Pgamma = 0.000115;
    double Xmin   = 0.143791;
    double Xmax   = 2.18736;

    G4double fCosAlphaMin, fCosAlphaMax;
    G4double fPsiMin, fPsiMax;
    G4double fVx, fVy, fT, fR, fAlpha;
};
//------------------------------------------------------------------------------
PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{
  in_file.open("Sr-Y-90_source.txt", std::ios::in);
  double kin_energy[48], prob[48];
  double x,y;
  int cntr=0;
  while(in_file  >> x >> y ){
    kin_energy[cntr]=x; prob[cntr]=y/3.12535; cntr++;
  }
  in_file.close();

  G4double alphaMin =   0*deg;      //alpha in [0,pi]
  G4double alphaMax = 180*deg;
  fCosAlphaMin = std::cos(alphaMin);
  fCosAlphaMax = std::cos(alphaMax);
  fPsiMin = 0*deg;       //psi in [0, 2*pi]
  fPsiMax = 360*deg;
}
//------------------------------------------------------------------------------
PrimaryGenerator::~PrimaryGenerator(){}
//------------------------------------------------------------------------------
void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

  G4double x0 = 0*mm, y0 = 0*mm, z0 = -1*mm;
  G4ThreeVector positionB(x0,y0,z0);

  G4ParticleDefinition* particleDefE = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  G4ParticleDefinition* particleDefG = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  G4PrimaryParticle* particle1;
  G4PrimaryParticle* particle2;

  particle1 = new G4PrimaryParticle(particleDefE);
  particle2 = new G4PrimaryParticle(particleDefG);

  do{
    fT = G4UniformRand()*(Xmax-Xmin);
    fR = G4UniformRand();
  }
  while( graph->Eval(fT,0,"S") > fR );

  double Me = particle1->GetMass() / MeV;
  double Ee = Me + fT;
  double Pze = sqrt(Ee*Ee - Me*Me);

  double Pzg = Egamma;


  do{
    fVx = G4UniformRand()*2.;
    fVy = G4UniformRand()*2.;
  }
  while (fVx*fVx + fVy*fVy > 2*2);
  positionB.setX( fVx*mm );
  positionB.setY( fVy*mm );
  positionB.setZ( G4UniformRand()*2.*mm );

  G4double cosAlpha, sinAlpha, psi;

  fAlpha = std::acos( G4UniformRand()*2. - 1. );

  sinAlpha = std::sin(fAlpha);
  cosAlpha = std::sqrt(1. - sinAlpha*sinAlpha);

  psi = G4UniformRand()*(fPsiMax - fPsiMin);

  particle1->SetMomentum(Pze*sinAlpha*std::cos(psi)*MeV,Pze*sinAlpha*std::sin(psi)*MeV,Pze*cosAlpha*MeV) ;
  particle2->SetMomentum(Pzg*sinAlpha*std::cos(psi)*MeV,Pzg*sinAlpha*std::sin(psi)*MeV,Pzg*cosAlpha*MeV) ;

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);

  if( G4UniformRand()<Pgamma)
    vertexB->SetPrimary(particle2);
  else
    vertexB->SetPrimary(particle1);

  event->AddPrimaryVertex(vertexB);

}
//==============================================================================
// PRIMARY GENERATOR ACTION
//==============================================================================
Sr90TESTPrimaryGeneratorAction::Sr90TESTPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fPrimaryGenerator(0)
{
  fPrimaryGenerator = new PrimaryGenerator();
}
//------------------------------------------------------------------------------
Sr90TESTPrimaryGeneratorAction::~Sr90TESTPrimaryGeneratorAction()
{
  delete fPrimaryGenerator;
}
//------------------------------------------------------------------------------
void Sr90TESTPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------
