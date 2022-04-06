#ifndef POWDERGAME_LIQUID_H
#define POWDERGAME_LIQUID_H

#include "Element.h"
#include "PowderGame.h"

class Liquid : public Element
{
public:
  Liquid( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge ) override {}
  void draw( PowderGame * pge ) override { pge->Draw( x, y, c ); }
};


#endif    // POWDERGAME_LIQUID_H
