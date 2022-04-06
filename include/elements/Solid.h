#ifndef POWDERGAME_SOLID_H
#define POWDERGAME_SOLID_H

#include "Element.h"
#include "PowderGame.h"

class Solid : public Element
{
public:
  Solid( int x, int y ) : Element( x, y ) {}
  void draw( PowderGame * pge ) override { pge->DrawElement( pos.x, pos.y, c ); }
};


#endif    // POWDERGAME_SOLID_H
