
#ifndef Sr90TESTActionInitialization_h
#define Sr90TESTActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class Sr90TESTActionInitialization : public G4VUserActionInitialization
{
  public:
    Sr90TESTActionInitialization();
    virtual ~Sr90TESTActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif

    
