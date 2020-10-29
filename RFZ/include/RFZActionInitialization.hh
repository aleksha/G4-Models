#ifndef RFZActionInitialization_h
#define RFZActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class RFZActionInitialization : public G4VUserActionInitialization
{
  public:
    RFZActionInitialization();
    virtual ~RFZActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


