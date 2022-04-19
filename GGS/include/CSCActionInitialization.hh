#ifndef CSCActionInitialization_h
#define CSCActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class CSCActionInitialization : public G4VUserActionInitialization
{
  public:
    CSCActionInitialization();
    virtual ~CSCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


