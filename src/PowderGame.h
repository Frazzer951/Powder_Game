#ifndef POWDERGAME_POWDERGAME_H
#define POWDERGAME_POWDERGAME_H

#include <ctime>

#include "elements/Element.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame : public olc::PixelGameEngine
{
private:
  std::unique_ptr<Element *[]> elements;
  int                          WIDTH;
  int                          HEIGHT;
  int                          iTargetFPS;
  float                        fTargetFrameTime;
  float                        fAccumulatedTime = 0.0f;


public:
  PowderGame()
  {
    sAppName = "Powder Game";
    std::srand( std::time( nullptr ) );
  }

  bool      OnUserCreate() override;
  bool      OnUserUpdate( float fElapsedTime ) override;
  bool      InRange( int x, int y );
  void      swap( int x0, int y0, int x1, int y1 );
  Element * GetElementAt( int x, int y );
  int       rand2() { return std::rand() % 2; }
};


#endif    // POWDERGAME_POWDERGAME_H
