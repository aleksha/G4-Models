#ifndef EPSActionInitialization_h
#define EPSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class EPSActionInitialization : public G4VUserActionInitialization
{
  public:
    EPSActionInitialization();
    virtual ~EPSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


