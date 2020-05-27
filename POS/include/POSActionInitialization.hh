#ifndef POSActionInitialization_h
#define POSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class POSActionInitialization : public G4VUserActionInitialization
{
  public:
    POSActionInitialization();
    virtual ~POSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


