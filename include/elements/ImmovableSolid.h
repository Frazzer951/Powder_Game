#ifndef POWDERGAME_IMMOVABLESOLID_H
#define POWDERGAME_IMMOVABLESOLID_H

#include "PowderGame.h"
#include "Solid.h"

class ImmovableSolid : public Solid
{
public:
  ImmovableSolid( int x, int y ) : Solid( x, y ) {}
  void update( PowderGame * pge, float fElapsedTime ) override {}
};


#endif    // POWDERGAME_IMMOVABLESOLID_H
