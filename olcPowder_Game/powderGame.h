#pragma once

#include "olcPixelGameEngine.h"
#include "powders.h"

bool DEBUG = false;

class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "Powder Game"; }

private:
  air *   AIR;
  sand *  SAND;
  water * WATER;
  stone * STONE;

  std::vector<air *> powderTypes;
  int                selectedPowderIndex = 0;
  int                numPowders          = 3;

  std::unique_ptr<air *[]> powders;
  int                      WIDTH;                   // Game World Width
  int                      HEIGHT;                  // Game World Height
  int                      powderSize       = 4;    // Size of a single Powder
  unsigned int             uBrushScale      = 1;
  bool                     bSimulate        = false;
  float                    fTargetFrameTime = 1.0f / 50.0f;    // Virtual FPS of 50fps
  float                    fAccumulatedTime = 0.0f;

public:
  bool             OnUserCreate() override;
  bool             OnUserUpdate( float fElapsedTime ) override;
  void             fillPowderCircle( int x, int y, air * type, int scale, bool replace = false );
  void             displayDebugInfo();
  void             takeUserInput();
  void             drawScreen();
  void             simulatePowders();
  std::vector<int> countPowders();

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }
  bool inRangeScreen( int x, int y )
  {
    return ( x >= 0 ) && ( x < ScreenWidth() ) && ( y >= 0 ) && ( y < ScreenHeight() );
  }
};