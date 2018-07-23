
#include "TPCPrimaryGeneratorAction.hh"

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

struct pg_Config {
  int    N_ev         ;
  double E_e          ;
  double Tp           ;
  double Pressure     ;
  double zTPC         ;
  double lTPC         ;
  int    MatMode      ;
  int    BeWindow     ;
  int    BeamSmearing ;
  double BeamTheta    ;
  double BeamPos      ;
};


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
    pg_Config loadConfig();

  private:
    std::ifstream myInFile   ;
    std::ifstream configFile ;
    int SimMode;
    int BeamSmearing;
    double Te;
    double BeamTheta;
    double BeamPos;
    int TrackProtons;
    int UseMuons;
    G4double fCosAlphaMin, fCosAlphaMax;      //solid angle
    G4double fPsiMin, fPsiMax;
    G4double fVy, fVx,fAlpha;
    pg_Config config;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{

  config = loadConfig();

  configFile.open("genCONFIG.txt", std::ios::in);
  int config_id;
  double config_value;
  while(configFile  >> config_id >> config_value){
   if(config_id== 1){Te           = config_value;}
   if(config_id== 4){SimMode      = config_value;}
   if(config_id==11){BeamSmearing = config_value;}
   if(config_id==12){BeamTheta    = config_value/1000.;}
   if(config_id==13){BeamPos      = config_value;}
   if(config_id==14){TrackProtons = config_value;}
   if(config_id==15){UseMuons     = config_value;}
  }
  configFile.close();

  if(SimMode==1){
    myInFile.open("generator.data", std::ios::in);
  }
  if(SimMode==3){
    myInFile.open("input.data", std::ios::in);
//    myInFile.open("input_true.data", std::ios::in);
  }

  G4double alphaMin =  0*deg;      //alpha in [0,pi]
  G4double alphaMax = 60*deg;
  fCosAlphaMin = std::cos(alphaMin);
  fCosAlphaMax = std::cos(alphaMax);

  fPsiMin = 0*deg;       //psi in [0, 2*pi]
  fPsiMax = 360*deg;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGenerator::~PrimaryGenerator()
{
  if( SimMode==1 || SimMode==3 ){myInFile.close();}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

pg_Config PrimaryGenerator::loadConfig()
{
  pg_Config tconfig;
  std::ifstream fin("config.txt");
  std::string line;
  while (getline(fin, line)) {
    std::istringstream sin(line.substr(line.find("=") + 1));
    if      (line.find("N_ev")         != 18446744073709551615ull ) sin >> tconfig.N_ev         ;
    else if (line.find("E_e")          != 18446744073709551615ull ) sin >> tconfig.E_e          ;
    else if (line.find("Tp")           != 18446744073709551615ull ) sin >> tconfig.Tp           ;
    else if (line.find("zTPC")         != 18446744073709551615ull ) sin >> tconfig.zTPC         ;
    else if (line.find("MatMode")      != 18446744073709551615ull ) sin >> tconfig.MatMode      ;
    else if (line.find("lTPC")         != 18446744073709551615ull ) sin >> tconfig.lTPC         ;
    else if (line.find("Pressure")     != 18446744073709551615ull ) sin >> tconfig.Pressure     ;
    else if (line.find("BeWindow")     != 18446744073709551615ull ) sin >> tconfig.BeWindow     ;
    else if (line.find("BeamSmearing") != 18446744073709551615ull ) sin >> tconfig.BeamSmearing ;
    else if (line.find("BeamTheta")    != 18446744073709551615ull ) sin >> tconfig.BeamTheta    ;
    else if (line.find("BeamPos")      != 18446744073709551615ull ) sin >> tconfig.BeamPos      ;

  }
  return tconfig;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

  G4ParticleDefinition* particleDefE  = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  G4ParticleDefinition* particleDefMu = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  G4ParticleDefinition* particleDefPi = G4ParticleTable::GetParticleTable()->FindParticle("pi-");
//  G4ParticleDefinition* particleDefP  = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  G4ParticleDefinition* particleDefP  = G4ParticleTable::GetParticleTable()->FindParticle("alpha");

  G4PrimaryParticle* particle1;
  G4PrimaryParticle* particle2;


  if(UseMuons<1)  particle1= new G4PrimaryParticle(particleDefE);
  else particle1 = new G4PrimaryParticle(particleDefMu);

  if(UseMuons<1)  particle2= new G4PrimaryParticle(particleDefE);
  else particle2 = new G4PrimaryParticle(particleDefMu);

  G4PrimaryParticle* particle3 = new G4PrimaryParticle(particleDefP);
  G4PrimaryParticle* particle4 = new G4PrimaryParticle(particleDefPi);
  G4PrimaryParticle* particle5 = new G4PrimaryParticle(particleDefMu);
  G4PrimaryParticle* particle6 = new G4PrimaryParticle(particleDefMu);
  G4PrimaryParticle* particleI = new G4PrimaryParticle();

  double Me = particle1->GetMass() / MeV;
  double Ee = Me + Te;
  double Pze = sqrt(Ee*Ee - Me*Me);



  int ev_id,p_code;
  double pxe , pye , pze , me , pxp , pyp , pzp , mp , vx , vy , vz , vt, theta;

  G4double x0 = 0*mm, y0 = 0*mm, z0 = -1499.999999*mm;
  G4ThreeVector positionB(x0,y0,z0);
  G4double timeB = 0.*ns;
  G4double cosAlpha, sinAlpha,psi;
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));

  if(BeamSmearing>0 && SimMode>0 && SimMode<2){
    do{
      fVx = G4UniformRand()*BeamPos;
      fVy = G4UniformRand()*BeamPos;
    }
    while (fVx*fVx + fVy*fVy > BeamPos*BeamPos);
    positionB.setX( fVx*mm );
    positionB.setY( fVy*mm );
   // G4cout << "Beam position: "
   //        << positionB.x() << " " << positionB.y() << " " << positionB.z() << " "
   //        <<  fVx*fVx + fVy*fVy << " " << BeamPos*BeamPos << G4endl;
  }

  if(SimMode==1){
    myInFile >> ev_id >> pxe >> pye >> pze >> me >> pxp >> pyp >> pzp >> mp >> vx >> vy >> vz >> vt >> theta;
    //G4cout << ev_id << " " << theta << G4endl;
    positionB.set(vx * mm, vy * mm, vz * mm);
    timeB = vt*ns;
    particle2->SetMomentum(pxe*MeV,pye*MeV,pze*MeV);
    particle6->SetMomentum(pxe*MeV,pye*MeV,pze*MeV);
    particle3->SetMomentum(pxp*MeV,pyp*MeV,pzp*MeV);
  }
  if(SimMode==3){
    myInFile >> ev_id >> p_code >> pxe >> pye >> pze >> vx >> vy >> vz >> vt ;
    positionB.set(vx * mm, vy * mm, vz * mm);
    timeB = vt*ns;
    particleI->SetPDGcode(p_code);
    particleI->SetMomentum(pxe*MeV,pye*MeV,pze*MeV);
    event->SetEventID(ev_id);
    //G4cout << ev_id << " " << p_code << G4endl;
  }
  if(SimMode==0 || SimMode==2){
    particle1->SetMomentum(0*MeV,0*MeV,Pze*MeV)   ;
    particle5->SetMomentum(0*MeV,0*MeV,Pze*MeV)   ;
    particle4->SetMomentum(0*MeV,0*MeV,Pze*MeV)   ;
    if(BeamSmearing>0){
      fAlpha = CLHEP::RandGauss::shoot(0,BeamTheta);
      fAlpha = std::sqrt(fAlpha*fAlpha);
      sinAlpha = std::sin(fAlpha);
      cosAlpha = std::sqrt(1. - sinAlpha*sinAlpha);
      psi = G4UniformRand()*(fPsiMax - fPsiMin);
      particle1->SetMomentum(Pze*sinAlpha*std::cos(psi)*MeV,Pze*sinAlpha*std::sin(psi)*MeV,Pze*cosAlpha*MeV)   ;
      particle5->SetMomentum(Pze*sinAlpha*std::cos(psi)*MeV,Pze*sinAlpha*std::sin(psi)*MeV,Pze*cosAlpha*MeV)   ;
      particle4->SetMomentum(Pze*sinAlpha*std::cos(psi)*MeV,Pze*sinAlpha*std::sin(psi)*MeV,Pze*cosAlpha*MeV)   ;
      //G4cout << "Beam momentum: " 
      //       << particle1->GetPx() << " " << particle1->GetPy() << " " << particle1->GetPz() 
      //       << "\t" << fAlpha << " " << BeamTheta << G4endl;  
    }
    //G4cout << "\n\n\n\n "<< Me << " " << Ee << " " << Pze << "\n\n\n\n\n\n" << G4endl;
  }

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, timeB);

  if(SimMode>0 && SimMode<2){
    vertexB->SetPrimary(particle2);
//    vertexB->SetPrimary(particle6);
    if(TrackProtons>0) vertexB->SetPrimary(particle3);  
  }
  
  if(SimMode<1){
    vertexB->SetPrimary(particle1);
//    vertexB->SetPrimary(particle5);
    //G4cout << "\n\n\n\n 111 "<< Me << " " << Ee << " " << Pze << "\n\n\n\n\n\n" << G4endl;
  }

  if(SimMode==2){
      vertexB->SetPrimary(particle1);
  }

  if(SimMode==3){
      vertexB->SetPrimary(particleI);
  }

  event->AddPrimaryVertex(vertexB);

}

//==============================================================================
// PRIMARY GENERATOR ACTION
//==============================================================================

TPCPrimaryGeneratorAction::TPCPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fPrimaryGenerator(0)
{ 
  fPrimaryGenerator = new PrimaryGenerator();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TPCPrimaryGeneratorAction::~TPCPrimaryGeneratorAction()
{
  delete fPrimaryGenerator;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TPCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}


