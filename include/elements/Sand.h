#ifndef POWDERGAME_SAND_H
#define POWDERGAME_SAND_H

#include "MovableSolid.h"

class Sand : public MovableSolid
{
private:
  std::vector<olc::Pixel> colors = { olc::Pixel( 166, 145, 80 ),  olc::Pixel( 177, 157, 94 ),
                                     olc::Pixel( 186, 168, 111 ), olc::Pixel( 194, 178, 128 ),
                                     olc::Pixel( 202, 188, 145 ), olc::Pixel( 211, 199, 162 ),
                                     olc::Pixel( 219, 209, 180 ) };


public:
  Sand( int x, int y ) : MovableSolid( x, y ) { c = colors[rand( 0, colors.size() )]; }
};


#endif    // POWDERGAME_SAND_H
