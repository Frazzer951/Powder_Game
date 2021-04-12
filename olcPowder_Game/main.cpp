#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

enum class powderType { air, sand, water };

class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "Powder Game"; }

private:
  std::unique_ptr<powderType[]> powders;

  unsigned int uBrushScale = 1;

  bool bSimulate = false;

  float fTargetFrameTime = 1.0f / 100.0f;    // Virtual FPS of 100fps
  float fAccumulatedTime = 0.0f;

public:
  bool OnUserCreate() override
  {
    powders = std::make_unique<powderType[]>( ScreenWidth() * ScreenHeight() );
    for( int y = 0; y < ScreenHeight(); y++ )
    {
      for( int x = 0; x < ScreenWidth(); x++ )
      {
        powders[y * ScreenWidth() + x] = powderType::air;
        if( x == 100 && y >= 95 && y < 105 ) powders[y * ScreenWidth() + x] = powderType::sand;
      }
    }

    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // Take user input
    if( GetMouse( 0 ).bHeld )    // Add sand on left click
    {
      fillPowderCircle( GetMouseX(), GetMouseY(), powderType::sand, uBrushScale );
    }
    if( GetMouse( 0 ).bHeld && GetKey( olc::Key::CTRL ).bHeld )    // Add sand on left click
    {
      fillPowderCircle( GetMouseX(), GetMouseY(), powderType::water, uBrushScale );
    }
    if( GetMouse( 1 ).bHeld )    // Set to air on right click
    {
      fillPowderCircle( GetMouseX(), GetMouseY(), powderType::air, uBrushScale );
    }
    if( GetKey( olc::Key::SPACE ).bPressed ) { bSimulate = !bSimulate; }    // Pause and Unpause simulation
    if( GetKey( olc::Key::NP_ADD ).bPressed ) { uBrushScale++; }            // Enlarge the brush
    if( GetKey( olc::Key::NP_SUB ).bPressed )                               // Shrink the brush
    {
      uBrushScale--;
      if( uBrushScale < 1 ) uBrushScale = 1;
    }

    // Only update the game at the specified frame rate
    fAccumulatedTime += fElapsedTime;
    if( fAccumulatedTime >= fTargetFrameTime )
    {
      fAccumulatedTime -= fTargetFrameTime;
      fElapsedTime = fTargetFrameTime;
    }
    else
      return true;    // Don't do anything this frame

    // Only update the simulation if the game is not paused
    if( bSimulate )
    {
      // Update powders
      for( int y = ScreenHeight() - 1; y >= 0; y-- )
      {
        for( int x = 0; x < ScreenWidth(); x++ )
        {
          switch( powders[y * ScreenWidth() + x] )
          {
            case powderType::air:    // Do nothing
              break;
            case powderType::sand:    // Update Sand
              moveSand( x, y );
              break;
            case powderType::water:    // Update Water
              moveWater( x, y );
              break;
            default: break;
          }
        }
      }
    }
    // Clear the screen
    Clear( olc::VERY_DARK_GREY );

    // Draw in powders
    for( int y = 0; y < ScreenHeight(); y++ )
    {
      for( int x = 0; x < ScreenWidth(); x++ )
      {
        switch( powders[y * ScreenWidth() + x] )
        {
          case powderType::air:    // Do nothing
            break;
          case powderType::sand:    // Draw Sand
            Draw( x, y, olc::Pixel( 194, 178, 128 ) );
            break;
          case powderType::water:    // Draw Water
            Draw( x, y, olc::Pixel( 0, 0, 255 ) );
            break;
        }
      }
    }

    // If Paused display how to unpause on screen
    if( !bSimulate ) DrawString( 0, 0, "Press SPACE to Unpause", olc::WHITE );

    // Display Brush Scale
    DrawString( 0, ScreenHeight() - 8, "Brush Scale: " + std::to_string( uBrushScale ), olc::WHITE );

    return true;
  }

  void fillPowderCircle( int x, int y, powderType type, int scale )
  {
    scale--;
    for( int i = -scale; i <= scale; i++ )
      for( int j = -scale; j <= scale; j++ )
        if( inRange( i + x, j + y ) && i * i + j * j <= scale * scale )
          powders[( j + y ) * ScreenWidth() + ( i + x )] = type;
  }

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < ScreenWidth() ) && ( y >= 0 ) && ( y < ScreenHeight() ); }

  void moveSand( int x, int y )
  {
    // Check 3 positions and move accordingly

    if( y + 1 >= ScreenWidth() ) return;

    if( movePowderDown( x, y, powderType::sand ) ) return;

    bool bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderDownLeft( x, y, powderType::sand ) ) return;
      if( movePowderDownRight( x, y, powderType::sand ) ) return;
    }
    else
    {
      if( movePowderDownRight( x, y, powderType::sand ) ) return;
      if( movePowderDownLeft( x, y, powderType::sand ) ) return;
    }
  }
  void moveWater( int x, int y )
  {
    // Check 5 positions and move accordingly
    // Similar to sand, but will also move left and right
    if( y + 1 >= ScreenWidth() ) return;

    if( movePowderDown( x, y, powderType::water ) ) return;

    bool bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderDownLeft( x, y, powderType::water ) ) return;
      if( movePowderDownRight( x, y, powderType::water ) ) return;
    }
    else
    {
      if( movePowderDownRight( x, y, powderType::water ) ) return;
      if( movePowderDownLeft( x, y, powderType::water ) ) return;
    }

    bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderLeft( x, y, powderType::water ) ) return;
      if( movePowderRight( x, y, powderType::water ) ) return;
    }
    else
    {
      if( movePowderRight( x, y, powderType::water ) ) return;
      if( movePowderLeft( x, y, powderType::water ) ) return;
    }
  }

  bool movePowderLeft( int x, int y, powderType type )
  {
    if( powders[y * ScreenWidth() + ( x - 1 )] == powderType::air && x - 1 >= 0 )
    {
      powders[y * ScreenWidth() + ( x - 1 )] = type;
      powders[y * ScreenWidth() + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderRight( int x, int y, powderType type )
  {
    if( powders[y * ScreenWidth() + ( x + 1 )] == powderType::air && x + 1 < ScreenWidth() )
    {
      powders[y * ScreenWidth() + ( x + 1 )] = type;
      powders[y * ScreenWidth() + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDown( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * ScreenWidth() + x] == powderType::air )
    {
      powders[( y + 1 ) * ScreenWidth() + x] = type;
      powders[y * ScreenWidth() + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDownLeft( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * ScreenWidth() + ( x - 1 )] == powderType::air && x - 1 >= 0 )
    {
      powders[( y + 1 ) * ScreenWidth() + ( x - 1 )] = type;
      powders[y * ScreenWidth() + x]                 = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDownRight( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * ScreenWidth() + ( x + 1 )] == powderType::air && x + 1 < ScreenWidth() )
    {
      powders[( y - 1 ) * ScreenWidth() + ( x + 1 )] = type;
      powders[y * ScreenWidth() + x]                 = powderType::air;
      return true;
    }
    return false;
  }
};

int main()
{
  PowderGame game;
  if( game.Construct( 200, 200, 4, 4 ) ) game.Start();
  return 0;
}