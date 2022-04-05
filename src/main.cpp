#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine/olcPixelGameEngine.h"


class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "PowderGame"; }

public:
  bool OnUserCreate() override
  {
    // Called once at the start, so create things here
    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // called once per frame
    for( int x = 0; x < ScreenWidth(); x++ )
      for( int y = 0; y < ScreenHeight(); y++ ) Draw( x, y, olc::Pixel( rand() % 255, rand() % 255, rand() % 255 ) );
    return true;
  }
};


int main()
{
  const int  WIDTH  = 240;
  const int  HEIGHT = 240;

  PowderGame pGame;
  if( pGame.Construct( WIDTH, HEIGHT, 4, 4 ) ) pGame.Start();

  return 0;
}