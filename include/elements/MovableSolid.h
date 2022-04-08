#ifndef POWDERGAME_MOVABLESOLID_H
#define POWDERGAME_MOVABLESOLID_H

#include "Liquid.h"
#include "PowderGame.h"
#include "Solid.h"

class MovableSolid : public Solid
{
public:
  float Y_Conversion_Rate = 1.0f;
  float Max_Bounce        = 100.0f;

  MovableSolid( int x, int y ) : Solid( x, y ) {}

  void update( PowderGame * pge, float fElapsedTime ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;

    // Check below
    if( !tryMove( pge, pos.x, pos.y + 1 ) )
    {
      // Check diagonal
      if( randZeroToOne() < 0.5 ) { tryMove( pge, pos.x + 1, pos.y + 1 ); }
      else
      {
        tryMove( pge, pos.x - 1, pos.y + 1 );
      }
    }
  }

  bool tryMove( PowderGame * pge, int x, int y )
  {
    if( pge->inRange( x, y ) )
    {
      if( pge->isEmpty( x, y ) || pge->isLiquid( x, y ) || pge->isGas( x, y ) )
      {
        pge->swap( pos.x, pos.y, x, y );
        return true;
      }
    }
    return false;
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
