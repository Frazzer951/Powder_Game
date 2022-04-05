#include "Gas.h"

#ifndef POWDERGAME_AIR_H
#  define POWDERGAME_AIR_H


class Air : public Gas
{
public:
  Air( int x, int y ) : Gas( x, y ) { c = olc::Pixel( 60, 60, 60 ); }
  void update() override {}
  void draw( olc::PixelGameEngine * pge ) override { pge->Draw( x, y, c ); }
};


#endif    // POWDERGAME_AIR_H
