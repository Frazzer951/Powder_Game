#ifndef POWDERGAME_LIQUID_H
#define POWDERGAME_LIQUID_H

#include "Element.h"
#include "PowderGame.h"

class Liquid : public Element
{
public:
  Liquid( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;
  }
  void draw( PowderGame * pge ) override { pge->DrawElement( x, y, c ); }
};


#endif    // POWDERGAME_LIQUID_H
