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

    // First try to fall down
    int new_x = x;
    int new_y = y + 1;
    if( pge->InRange( new_x, new_y )
        && ( dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) )
             || dynamic_cast<Liquid *>( pge->GetElementAt( new_x, new_y ) ) ) )
    {
      pge->swap( x, y, new_x, new_y );
    }
    else
    {
      // Pick random Direction
      int dir = pge->rand2();

      // Try to move diagonally
      new_x = x + ( ( dir == 0 ) ? 1 : -1 );
      if( pge->InRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
      {
        pge->swap( x, y, new_x, new_y );
      }
      else    // Try other direction
      {
        new_x = x + ( ( dir == 1 ) ? 1 : -1 );
        if( pge->InRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
        {
          pge->swap( x, y, new_x, new_y );
        }
      }
    }
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
