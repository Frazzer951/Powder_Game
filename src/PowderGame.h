#ifndef POWDERGAME_POWDERGAME_H
#define POWDERGAME_POWDERGAME_H

#include <ctime>
#include <string>
#include <vector>

#include "elements/Element.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame : public olc::PixelGameEngine
{
private:
  std::unique_ptr<Element *[]> elements;
  std::vector<std::string>     powderTypes;
  int                          WIDTH;                      // Game World Width
  int                          HEIGHT;                     // Game World Height
  int                          powderSize          = 4;    // Size of a single Powder
  int                          selectedPowderIndex = 0;
  unsigned int                 BrushScale          = 1;
  int                          iTargetFPS;
  float                        fTargetFrameTime;
  float                        fAccumulatedTime = 0.0f;
  bool                         simulate;
  bool                         updated;


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
  void      takeUserInput();
  void      drawScreen();
  void      DrawElement( int x, int y, olc::Pixel c );
  Element * GetElementAt( int x, int y );
  Element * CreateElement( std::string element_name );
  int       rand2() { return std::rand() % 2; }
  void      PowderGame::fillPowderCircle( int x, int y, std::string type, int scale, bool replace );
  bool      isUpdated() const { return updated; }
};


#endif    // POWDERGAME_POWDERGAME_H
