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


  bool actOnNeighboringElement( PowderGame * pge, Element * elem, int x, int y, bool isFinal, bool isFirst,
                                vec2i lastValid, int depth ) override
  {
    if( pge->isEmpty( elem->getPos() ) )
    {
      setAdjacentFreeFalling( pge, depth, lastValid );
      if( isFinal )
      {
        freeFalling = true;
        pge->swap( pos, elem->getPos() );
      }
      else
      {
        return false;
      }
    }
    else if( pge->isSolid( elem->getPos() ) )
    {
      if( isFinal )
      {
        moveToLastValid( pge, lastValid );
        return true;
      }
      if( freeFalling )
      {
        // Convert part of y-vel to x-vel when hitting ground
        float absY = abs( vel.y ) / Y_Conversion_Rate;
        vel.x += ( randZeroToOne() < 0.5 ) ? -absY : absY;
      }

      // vec2f normVel = vec2f( vel ).normalize();
      // int   addX    = getAdditional( normVel.x );
      // int   addY    = getAdditional( normVel.y );


      freeFalling = false;
      moveToLastValid( pge, lastValid );
      return true;
    }
    else if( pge->isGas( elem->getPos() ) )
    {
      if( isFinal )
      {
        moveToLastValidAndSwap( pge, elem, lastValid );
        return true;
      }
      return false;
    }
    else if( pge->isLiquid( elem->getPos() ) )
    {
      moveToLastValidAndSwap( pge, elem, lastValid );
      return true;
    }
    return false;
  }

  void setAdjacentFreeFalling( PowderGame * pge, int depth, vec2i lastValid )
  {
    if( depth > 0 ) return;

    Element * adjElem1 = pge->GetElementAt( pos.x + 1, pos.y );
    if( pge->isSolid( adjElem1->getPos() ) ) { setElementFreeFalling( adjElem1 ); }

    Element * adjElem2 = pge->GetElementAt( pos.x - 1, pos.y );
    if( pge->isSolid( adjElem2->getPos() ) ) { setElementFreeFalling( adjElem2 ); }
  }

  int getAdditional( float val )
  {
    if( val < -.1f ) { return (int) floor( val ); }
    else if( val > .1f )
    {
      return (int) ceil( val );
    }
    else
    {
      return 0;
    }
  }

  float getAverageVelOrGravity( float vel, float otherVel )
  {
    if( otherVel < 125.0f ) { return 124.0f; }
    float avg = ( vel + otherVel ) / 2;
    if( avg > 0.0f ) { return avg; }
    else
    {
      return std::max( avg, 124.0f );
    }
  }

  bool setElementFreeFalling( Element * element )
  {
    element->freeFalling = ( randZeroToOne() >= element->inertialResistance ) || element->freeFalling;
    return element->freeFalling;
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
