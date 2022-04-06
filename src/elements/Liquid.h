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

    // First try to fall down
    int new_x = x;
    int new_y = y + 1;
    if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
    {
      pge->swap( x, y, new_x, new_y );
    }
    else
    {
      // Pick random Direction
      int dir = pge->rand2();

      // Try to move diagonally
      new_x = x + ( ( dir == 0 ) ? 1 : -1 );
      if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
      {
        pge->swap( x, y, new_x, new_y );
      }
      else    // Try other direction
      {
        new_x = x + ( ( dir == 1 ) ? 1 : -1 );
        if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
        {
          pge->swap( x, y, new_x, new_y );
        }
        else
        {
          // Try left or right
          // Pick random Direction
          int dir = pge->rand2();

          // Try to move diagonally
          new_x = x + ( ( dir == 0 ) ? 1 : -1 );
          new_y = y;

          if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
          {
            pge->swap( x, y, new_x, new_y );
          }
          else    // Try other direction
          {
            new_x = x + ( ( dir == 1 ) ? 1 : -1 );
            if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
            {
              pge->swap( x, y, new_x, new_y );
            }
          }
        }
      }
    }
  }
  void draw( PowderGame * pge ) override { pge->DrawElement( x, y, c ); }
};


#endif    // POWDERGAME_LIQUID_H
