#ifndef POWDERGAME_GAS_H
#define POWDERGAME_GAS_H

#include "Element.h"
#include "PowderGame.h"

class Gas : public Element
{
public:
  Gas( int x, int y ) : Element( x, y ) {}
  void update( PowderGame * pge ) override
  {
    // Only update once per cycle
    if( updated == pge->isUpdated() ) { return; }
    updated = !updated;
  }
  void draw( PowderGame * pge ) override { pge->DrawElement( pos.x, pos.y, c ); }
  bool actOnNeighboringElement( Element * neighbor, int modifiedMatrixX, int modifiedMatrixY, boolean isFinal,
                                boolean isFirst, vec2i lastValidLocation, int depth ) override
  {
    return true;
  }
};


#endif    // POWDERGAME_GAS_H
