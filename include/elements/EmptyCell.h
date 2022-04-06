#ifndef POWDERGAME_EMPTYCELL_H
#define POWDERGAME_EMPTYCELL_H

#include "Element.h"

class EmptyCell : public Element
{
public:
  EmptyCell( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge, float fElapsedTime ) override {}
  void draw( PowderGame * pge ) override {}
  bool actOnNeighboringElement( PowderGame * pge, Element * elem, int x, int y, bool isFinal, bool isFirst,
                                vec2i lastValid, int depth ) override
  {
    return true;
  }
};


#endif    // POWDERGAME_EMPTYCELL_H
