#ifndef ZMSActionInitialization_h
#define ZMSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ZMSActionInitialization : public G4VUserActionInitialization
{
  public:
    ZMSActionInitialization();
    virtual ~ZMSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


