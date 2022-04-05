#ifndef POWDERGAME_POWDERGAME_H
#define POWDERGAME_POWDERGAME_H


#include "elements/Element.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame : public olc::PixelGameEngine
{
private:
  std::unique_ptr<Element *[]> elements;
  int                          WIDTH;
  int                          HEIGHT;

public:
  PowderGame() { sAppName = "Powder Game"; }

  bool      OnUserCreate() override;
  bool      OnUserUpdate( float fElapsedTime ) override;
  Element * GetElementAt( int x, int y );
};


#endif    // POWDERGAME_POWDERGAME_H
