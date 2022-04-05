#include "Element.h"

#ifndef POWDERGAME_SOLID_H
#  define POWDERGAME_SOLID_H


class Solid : public Element
{
public:
  Solid( int x, int y ) : Element( x, y ) {}
};


#endif    // POWDERGAME_SOLID_H
