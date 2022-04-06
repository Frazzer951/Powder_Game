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
    return true;
  }
};


#endif    // POWDERGAME_MOVABLESOLID_H
