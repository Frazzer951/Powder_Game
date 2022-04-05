#include "Color.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

#ifndef POWDERGAME_ELEMENT_H
#  define POWDERGAME_ELEMENT_H


class Element
{
public:
  virtual void update()                           = 0;
  virtual void draw( olc::PixelGameEngine * pge ) = 0;

protected:
  Color c;
};


#endif    // POWDERGAME_ELEMENT_H
