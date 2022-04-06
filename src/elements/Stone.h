#ifndef POWDERGAME_STONE_H
#define POWDERGAME_STONE_H

#include "ImmovableSolid.h"

class Stone : public ImmovableSolid
{
public:
  Stone( int x, int y ) : ImmovableSolid( x, y ) { c = olc::Pixel( 136, 140, 141 ); }
};


#endif    // POWDERGAME_STONE_H
