#ifndef POWDERGAME_LIQUID_H
#define POWDERGAME_LIQUID_H

#include "Element.h"
#include "PowderGame.h"

class Liquid : public Element
{
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
      // Check diagonal
      if( randZeroToOne() < 0.5 ) { tryMove( pge, pos.x + 1, pos.y ); }
      else
      {
        tryMove( pge, pos.x - 1, pos.y );
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
