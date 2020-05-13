#ifndef STLActionInitialization_h
#define STLActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class STLActionInitialization : public G4VUserActionInitialization
{
  public:
    STLActionInitialization();
    virtual ~STLActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


