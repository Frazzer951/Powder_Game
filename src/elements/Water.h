#ifndef POWDERGAME_WATER_H
#define POWDERGAME_WATER_H

#include "Liquid.h"

class Water : public Liquid
{
public:
  Water( int x, int y ) : Liquid( x, y ) { c = olc::Pixel( 15, 94, 156 ); }
};


#endif    // POWDERGAME_WATER_H
