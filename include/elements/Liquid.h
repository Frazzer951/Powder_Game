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
    int new_x = pos.x;
    int new_y = pos.y + 1;
    if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
    {
      pge->swap( pos.x, pos.y, new_x, new_y );
    }
    else
    {
      // Pick random Direction
      int dir = pge->rand2();

      // Try to move diagonally
      new_x = pos.x + ( ( dir == 0 ) ? 1 : -1 );
      if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
      {
        pge->swap( pos.x, pos.y, new_x, new_y );
      }
      else    // Try other direction
      {
        new_x = pos.x + ( ( dir == 1 ) ? 1 : -1 );
        if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
        {
          pge->swap( pos.x, pos.y, new_x, new_y );
        }
        else
        {
          // Try left or right
          // Pick random Direction
          int dir = pge->rand2();

          // Try to move diagonally
          new_x = pos.x + ( ( dir == 0 ) ? 1 : -1 );
          new_y = pos.y;

          if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
          {
            pge->swap( pos.x, pos.y, new_x, new_y );
          }
          else    // Try other direction
          {
            new_x = pos.x + ( ( dir == 1 ) ? 1 : -1 );
            if( pge->inRange( new_x, new_y ) && dynamic_cast<EmptyCell *>( pge->GetElementAt( new_x, new_y ) ) )
            {
              pge->swap( pos.x, pos.y, new_x, new_y );
            }
          }
        }
      }
    }
  }
  void draw( PowderGame * pge ) override { pge->DrawElement( pos.x, pos.y, c ); }
  bool actOnNeighboringElement( Element * neighbor, int x, int y, bool isFinal, bool isFirst, vec2i lastValid,
                                int depth ) override
  {
    return true;
  }
};


#endif    // POWDERGAME_LIQUID_H
