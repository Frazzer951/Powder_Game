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

    vel += pge->getGravity();
    if( freeFalling ) { vel.x *= 0.9; }

    vel.clamp( -200, 200 );

    int   yModifier     = vel.y < 0 ? -1 : 1;
    int   xModifier     = vel.x < 0 ? -1 : 1;
    float velXDeltaTime = abs( vel.x ) * fElapsedTime;
    float velYDeltaTime = abs( vel.y ) * fElapsedTime;
    bool  xDiffIsLarger = abs( velXDeltaTime ) > abs( velYDeltaTime );

    int   upperBound = std::max( abs( velXDeltaTime ), abs( velYDeltaTime ) );
    int   min        = std::min( abs( velXDeltaTime ), abs( velYDeltaTime ) );
    float slope      = ( min == 0 || upperBound == 0 ) ? 0 : ( (float) ( min ) / ( upperBound ) );

    int   smallerCount;
    vec2i formerPos = vec2i( pos );
    vec2i lastValid = vec2i( pos );
    for( int i = 1; i <= upperBound; i++ )
    {
      smallerCount = round( i * slope );
      int yIncrease, xIncrease;
      if( xDiffIsLarger )
      {
        xIncrease = i;
        yIncrease = smallerCount;
      }
      else
      {
        xIncrease = smallerCount;
        yIncrease = i;
      }
      int new_x = pos.x + ( xIncrease * xModifier );
      int new_y = pos.y + ( yIncrease * yModifier );
      if( pge->inRange( new_x, new_y ) )
      {
        Element * neighbor = pge->GetElementAt( new_x, new_y );
        if( neighbor == this ) continue;
        bool stopped = actOnNeighboringElement( pge, neighbor, new_x, new_y, i == upperBound, i == 1, lastValid, 0 );
        if( stopped ) { break; }
        lastValid = vec2i( new_x, new_y );
      }
      else
      {
        pge->swap( pos, lastValid );
      }
    }
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
