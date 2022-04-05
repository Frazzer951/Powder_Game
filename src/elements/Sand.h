#include "PowderGame.h"

#include "elements/Solid.h"

#ifndef POWDERGAME_SAND_H
#  define POWDERGAME_SAND_H


class Sand : public Solid
{
public:
  Sand( int x, int y ) : Solid( x, y ) { c = olc::Pixel( 194, 178, 128 ); }
  void update( PowderGame * pge ) override {}
  void draw( PowderGame * pge ) override { pge->Draw( x, y, c ); }
};


#endif    // POWDERGAME_SAND_H
