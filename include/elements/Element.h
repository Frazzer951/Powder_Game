#ifndef POWDERGAME_ELEMENT_H
#define POWDERGAME_ELEMENT_H

#include "vec2.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame;

class Element
{
public:
  Element( int x, int y ) : pos( { x, y } ) {}
  Element( vec2i pos ) : pos( pos ) {}
  virtual void update( PowderGame * pge, float fElapsedTime )        = 0;
  virtual void draw( PowderGame * pge )                              = 0;

  void          setPosition( vec2i new_pos );
  void          setPosition( int new_x, int new_y );
  int           rand( int from, int to ) { return std::rand() % ( to - from ) + from; }
  double        randZeroToOne() { return std::rand() / ( RAND_MAX + 1. ); }
  const vec2i & getPos() const { return pos; }

protected:
  bool       updated;
  vec2i      pos;
  olc::Pixel c;

public:
  bool  freeFalling        = true;
};


#endif    // POWDERGAME_ELEMENT_H
