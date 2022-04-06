#ifndef POWDERGAME_AIR_H
#define POWDERGAME_AIR_H

#include "Gas.h"
#include "PowderGame.h"

class Air : public Gas
{
public:
  Air( int x, int y ) : Gas( x, y ) { c = olc::Pixel( 60, 60, 60 ); }
};


#endif    // POWDERGAME_AIR_H
