#include "olcPixelGameEngine/olcPixelGameEngine.h"

#ifndef POWDERGAME_ELEMENT_H
#  define POWDERGAME_ELEMENT_H


class Element
{
public:
  Element( int x, int y ) : x( x ), y( y ) {}
  virtual void update( olc::PixelGameEngine * pge ) = 0;
  virtual void draw( olc::PixelGameEngine * pge )   = 0;

protected:
  int        x;
  int        y;
  olc::Pixel c;
};


#endif    // POWDERGAME_ELEMENT_H
