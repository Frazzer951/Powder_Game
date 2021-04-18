#pragma once

#include "air.h"
#include "olcPixelGameEngine.h"
#include "sand.h"

bool DEBUG = false;

enum class powderTypes { AIR, SAND };

std::string powderEnumToString( powderTypes type )
{
  switch( type )
  {
    case powderTypes::AIR: return "Air";
    case powderTypes::SAND: return "Sand";
  }
}

class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "Powder Game"; }

private:
  std::vector<powderTypes> selectablePowders   = { powderTypes::SAND };
  int                      selectedPowderIndex = 0;
  int                      numPowders          = 1;

  std::unique_ptr<air *[]> powders;
  int                      WIDTH;              // Game World Width
  int                      HEIGHT;             // Game World Height
  int                      powderSize  = 4;    // Size of a single Powder
  unsigned int             uBrushScale = 1;
  bool                     bSimulate   = false;

public:
  float gravity = 9.8f;

  bool  OnUserCreate() override;
  bool  OnUserUpdate( float fElapsedTime ) override;
  void  fillPowderCircle( int x, int y, powderTypes type, int scale, bool replace );
  void  displayDebugInfo();
  void  takeUserInput();
  void  drawScreen();
  void  simulatePowders( float fElapsedTime );
  float clamp( float value, float min, float max );
  int   cordToIndex( int x, int y );
  air * getParticleAt( int x, int y );
  air * makeParticle( powderTypes type );

  std::vector<int> countPowders();

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }
  bool inRangeScreen( int x, int y )
  {
    return ( x >= 0 ) && ( x < ScreenWidth() ) && ( y >= 0 ) && ( y < ScreenHeight() );
  }
};