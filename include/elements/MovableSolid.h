#ifndef POWDERGAME_MOVABLESOLID_H
#define POWDERGAME_MOVABLESOLID_H

#include "Liquid.h"
#include "PowderGame.h"
#include "Solid.h"

class MovableSolid : public Solid
{
public:
  MovableSolid( int x, int y ) : Solid( x, y ) {}

  void update( PowderGame * pge ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;

    vel.y += pge->getGravity().y;
    if( freeFalling ) { vel.x *= 0.9; }
  }

  bool actOnNeighboringElement( Element * neighbor, int x, int y, bool isFinal, bool isFirst, vec2i lastValid,
                                int depth ) override
  {
    return true;
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
