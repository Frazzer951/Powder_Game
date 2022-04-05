#include "olcPixelGameEngine/olcPixelGameEngine.h"

#ifndef POWDERGAME_ELEMENT_H
#  define POWDERGAME_ELEMENT_H

class PowderGame;

class Element
{
public:
  Element( int x, int y ) : x( x ), y( y ) {}
  virtual void update( PowderGame * pge ) = 0;
  virtual void draw( PowderGame * pge )   = 0;

protected:
  int        x;
  int        y;
  olc::Pixel c;
};


#endif    // POWDERGAME_ELEMENT_H
