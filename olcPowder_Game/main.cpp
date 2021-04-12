#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

enum powderType { air, sand };

class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "Powder Game"; }

private:
  std::unique_ptr<powderType[]> powders;

public:
  bool OnUserCreate() override
  {
    powders = std::make_unique<powderType[]>( ScreenWidth() * ScreenHeight() );
    for( int y = 0; y < ScreenWidth(); y++ )
    {
      for( int x = 0; x < ScreenHeight(); x++ ) { powders[y * ScreenHeight() + x] = air; }
    }

    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // Clear the screen
    Clear( olc::DARK_BLUE );

    return true;
  }
};

int main()
{
  PowderGame game;
  if( game.Construct( 500, 500, 2, 2 ) ) game.Start();
  return 0;
}