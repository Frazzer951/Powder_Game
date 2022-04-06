#ifndef POWDERGAME_ELEMENT_H
#define POWDERGAME_ELEMENT_H

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame;

class Element
{
public:
  Element( int x, int y ) : x( x ), y( y ) {}
  virtual void update( PowderGame * pge ) = 0;
  virtual void draw( PowderGame * pge )   = 0;
  void         setPosition( int new_x, int new_y )
  {
    x = new_x;
    y = new_y;
  }

protected:
  int        x;
  int        y;
  bool       updated;
  olc::Pixel c;
};


#endif    // POWDERGAME_ELEMENT_H
