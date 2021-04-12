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
    for( int y = 0; y < ScreenHeight(); y++ )
    {
      for( int x = 0; x < ScreenWidth(); x++ )
      {
        powders[y * ScreenWidth() + x] = air;
        //if( x >= 95 && x <= 105 && y >= 95 && y < 105 ) powders[y * ScreenWidth() + x] = sand;
        if( x == 100 && y >= 95 && y < 105 ) powders[y * ScreenWidth() + x] = sand;
      }
    }

    /*powders[99 * ScreenWidth() + 100]  = sand;
    powders[100 * ScreenWidth() + 100] = sand;
    powders[101 * ScreenWidth() + 100] = sand;
    powders[102 * ScreenWidth() + 100] = sand;*/

    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // Update powders
    for( int y = ScreenHeight() - 1; y >= 0; y-- )
    {
      for( int x = 0; x < ScreenWidth(); x++ )
      {
        switch( powders[y * ScreenWidth() + x] )
        {
          case air:    // Do nothing
            break;
          case sand:    // Update Sand
            moveSand( x, y );
            break;
          default: break;
        }
      }
    }

    // Clear the screen
    Clear( olc::DARK_BLUE );

    // Draw in powders
    for( int y = 0; y < ScreenHeight(); y++ )
    {
      for( int x = 0; x < ScreenWidth(); x++ )
      {
        switch( powders[y * ScreenWidth() + x] )
        {
          case air:    // Do nothing
            break;
          case sand:    // Draw Boundary
            Draw( x, y, olc::Pixel( 194, 178, 128 ) );
            break;
        }
      }
    }

    return true;
  }

  void moveSand( int x, int y )
  {
    // Check 3 positions and move accordingly

    if( y + 1 >= ScreenWidth() ) return;

    if( powders[( y + 1 ) * ScreenWidth() + x] == air )
    {
      // Check below
      powders[( y + 1 ) * ScreenWidth() + x] = sand;
      powders[y * ScreenWidth() + x]         = air;
    }
    else if( powders[( y + 1 ) * ScreenWidth() + ( x - 1 )] == air && x - 1 >= 0 )
    {
      // Check down left
      powders[( y + 1 ) * ScreenWidth() + ( x - 1 )] = sand;
      powders[y * ScreenWidth() + x]                 = air;
    }
    else if( powders[( y + 1 ) * ScreenWidth() + ( x + 1 )] == air && x + 1 < ScreenWidth() )
    {
      // Check down right
      powders[( y - 1 ) * ScreenWidth() + ( x + 1 )] = sand;
      powders[y * ScreenWidth() + x]                 = air;
    }
  }
};

int main()
{
  PowderGame game;
  if( game.Construct( 200, 200, 4, 4 ) ) game.Start();
  return 0;
}