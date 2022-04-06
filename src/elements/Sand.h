#include "PowderGame.h"

#include "elements/Solid.h"

#ifndef POWDERGAME_SAND_H
#  define POWDERGAME_SAND_H


class Sand : public Solid
{
public:
  Sand( int x, int y ) : Solid( x, y ) { c = olc::Pixel( 194, 178, 128 ); }
  void update( PowderGame * pge ) override
  {
    // First try to fall down
    int new_x = x;
    int new_y = y + 1;
    if( pge->InRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
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
  void draw( PowderGame * pge ) override { pge->Draw( x, y, c ); }
};


#endif    // POWDERGAME_SAND_H
