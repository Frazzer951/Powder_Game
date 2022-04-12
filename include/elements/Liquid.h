#ifndef POWDERGAME_LIQUID_H
#define POWDERGAME_LIQUID_H

#include "Element.h"
#include "PowderGame.h"

class Liquid : public Element
{
private:
  int dispersion_rate = 5;

public:
  Liquid( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge, float fElapsedTime ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;

    // Check below
    if( !tryMove( pge, pos.x, pos.y + 1 ) )
    {
      // Check to side
      vec2i i_pos = pos;
      int dir = randZeroToOne() < 0.5 ? -1 : 1;
      for( int i = 1; i <= dispersion_rate; i++ )
      {
        if( tryMove( pge, i_pos.x + ( dir * dispersion_rate ), i_pos.y ) ) { break; }
      }
    }
  }
  bool tryMove( PowderGame * pge, int x, int y )
  {
    if( pge->inRange( x, y ) )
    {
      if( pge->isEmpty( x, y ) || pge->isGas( x, y ) )
      {
        pge->swap( pos.x, pos.y, x, y );
        return true;
      }
    }
    return false;
  }
  void draw( PowderGame * pge ) override { pge->DrawElement( pos.x, pos.y, c ); }
};


#endif    // POWDERGAME_LIQUID_H
