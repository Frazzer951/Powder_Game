#ifndef POWDERGAME_EMPTYCELL_H
#define POWDERGAME_EMPTYCELL_H

#include "Element.h"

class EmptyCell : public Element
{
public:
  EmptyCell( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge ) override {}
  void draw( PowderGame * pge ) override {}
};


#endif    // POWDERGAME_EMPTYCELL_H
