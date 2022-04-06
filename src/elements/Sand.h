#ifndef POWDERGAME_SAND_H
#define POWDERGAME_SAND_H

#include "MovableSolid.h"

class Sand : public MovableSolid
{
public:
  Sand( int x, int y ) : MovableSolid( x, y ) { c = olc::Pixel( 194, 178, 128 ); }
};


#endif    // POWDERGAME_SAND_H
