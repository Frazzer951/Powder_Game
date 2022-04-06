#ifndef POWDERGAME_STONE_H
#define POWDERGAME_STONE_H

#include "ImmovableSolid.h"

class Stone : public ImmovableSolid
{
private:
  std::vector<olc::Pixel> colors = { olc::Pixel( 136, 140, 141 ), olc::Pixel( 98, 102, 102 ),
                                     olc::Pixel( 111, 114, 115 ), olc::Pixel( 123, 127, 128 ) };


public:
  Stone( int x, int y ) : ImmovableSolid( x, y ) { c = colors[rand( 0, colors.size() )]; }
};


#endif    // POWDERGAME_STONE_H
