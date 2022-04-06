#ifndef POWDERGAME_IMMOVABLESOLID_H
#define POWDERGAME_IMMOVABLESOLID_H

#include "PowderGame.h"
#include "Solid.h"

class ImmovableSolid : public Solid
{
public:
  ImmovableSolid( int x, int y ) : Solid( x, y ) {}
  void update( PowderGame * pge ) override {}
  bool actOnNeighboringElement( Element * neighbor, int x, int y, bool isFinal, bool isFirst, vec2i lastValid,
                                int depth ) override
  {
    return true;
  }
};


#endif    // POWDERGAME_IMMOVABLESOLID_H
