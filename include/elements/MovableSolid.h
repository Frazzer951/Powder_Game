#ifndef POWDERGAME_MOVABLESOLID_H
#define POWDERGAME_MOVABLESOLID_H

#include "Liquid.h"
#include "PowderGame.h"
#include "Solid.h"

class MovableSolid : public Solid
{
public:
  MovableSolid( int x, int y ) : Solid( x, y ) {}

  void update( PowderGame * pge, float fElapsedTime ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;

    vel.x += pge->getGravity().x;
    vel.y += pge->getGravity().y;
    if( freeFalling ) { vel.x *= 0.9; }

    int   yModifier       = vel.y < 0 ? -1 : 1;
    int   xModifier       = vel.x < 0 ? -1 : 1;
    float velXDeltaTime_F = abs( vel.x ) * fElapsedTime;
    float velYDeltaTIme_F = abs( vel.y ) * fElapsedTime;
    int   velXDeltaTime;
    int   velYDeltaTime;

    // Calculate velXDeltaTime
    if( velXDeltaTime_F < 0 )
    {
      xThreshold += velXDeltaTime_F;
      velXDeltaTime = (int) xThreshold;
      if( abs( velXDeltaTime ) > 0 ) { xThreshold = 0; }
    }
    else
    {
      xThreshold    = 0;
      velXDeltaTime = (int) velXDeltaTime_F;
    }

    // Calculate velYDeltaTime
    if( velYDeltaTIme_F < 0 )
    {
      yThreshold += velYDeltaTIme_F;
      velYDeltaTime = (int) yThreshold;
      if( abs( velYDeltaTime ) > 0 ) { yThreshold = 0; }
    }
    else
    {
      yThreshold    = 0;
      velYDeltaTime = (int) velYDeltaTIme_F;
    }

    bool xDiffIsLarger = abs( velXDeltaTime ) > abs( velYDeltaTime );

    int   upperBound = std::max( abs( velXDeltaTime ), abs( velYDeltaTime ) );
    int   min        = std::min( abs( velXDeltaTime ), abs( velYDeltaTime ) );
    float slope      = ( min == 0 || upperBound == 0 ) ? 0 : ( (float) ( min + 1 ) / ( upperBound + 1 ) );

    int   smallerCount;
    vec2i formerPos = vec2i( pos );
    vec2i lastValid = vec2i( pos );
    for( int i = 0; i <= upperBound; i++ )
    {
      smallerCount = floor( i * slope );
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
    else if( pge->isLiquid( elem->getPos() ) )
    {
      if( depth > 0 )
      {
        freeFalling = true;
        setAdjacentFreeFalling( pge, depth, lastValid );
        pge->swap( pos, elem->getPos() );
      }
      else
      {
        freeFalling = true;
        moveToLastValidAndSwap( pge, elem, lastValid );
        return true;
      }
    }
    else if( pge->isSolid( elem->getPos() ) )
    {
      if( depth > 0 ) { return true; }
      if( isFinal )
      {
        moveToLastValid( pge, lastValid );
        return true;
      }
      if( freeFalling )
      {
        float absY = std::min( abs( vel.y ) / 31, -105 );
        vel.x      = vel.x < 0 ? -absY : absY;
      }
      vec2i normVel = vec2i( vel ).normalize();
      int   addX    = getAdditional( normVel.x );
      int   addY    = getAdditional( normVel.y );

      Element * diagElem = pge->GetElementAt( pos.x + addX, pos.y + addY );
      if( isFirst ) { vel.y = getAverageVelOrGravity( vel.y, elem->vel.y ); }
      else
      {
        vel.y = 124;
      }

      elem->vel.y = vel.y;
      vel.x *= frictionFactor * elem->frictionFactor;
      if( !pge->isEmpty( diagElem->getPos() ) )
      {
        bool stoppedDiag =
            actOnNeighboringElement( pge, diagElem, pos.x + addX, pos.y + addY, true, false, lastValid, depth + 1 );
        if( !stoppedDiag )
        {
          freeFalling = true;
          return true;
        }
      }

      Element * adjElem = pge->GetElementAt( pos.x + addX, pos.y );
      if( !pge->isEmpty( adjElem->getPos() ) && adjElem != diagElem )
      {
        bool stoppedAdj =
            actOnNeighboringElement( pge, adjElem, pos.x + addX, pos.y, true, false, lastValid, depth + 1 );
        if( stoppedAdj ) { vel.x *= -1; }
        else

        {
          freeFalling = false;
          return true;
        }
      }

      freeFalling = false;

      moveToLastValid( pge, lastValid );
      return true;
    }
    else if( pge->isLiquid( elem->getPos() ) )
    {
      if( isFinal )
      {
        moveToLastValidAndSwap( pge, elem, lastValid );
        return true;
      }
      return false;
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
    element->freeFalling = randZeroToOne() > element->inertialResistance || element->freeFalling;
    return element->freeFalling;
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
