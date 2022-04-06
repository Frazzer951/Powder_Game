#ifndef POWDERGAME_GAS_H
#define POWDERGAME_GAS_H

#include "Element.h"
#include "PowderGame.h"

class Gas : public Element
{
public:
  Gas( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge ) override {}
  void draw( PowderGame * pge ) override { pge->Draw( x, y, c ); }
};


#endif    // POWDERGAME_GAS_H
