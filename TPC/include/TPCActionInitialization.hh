
#ifndef TPCActionInitialization_h
#define TPCActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TPCActionInitialization : public G4VUserActionInitialization
{
  public:
    TPCActionInitialization();
    virtual ~TPCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
