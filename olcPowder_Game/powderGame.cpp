#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "powders.h"

bool DEBUG = false;

//enum class powderType { air, sand, water };

class PowderGame : public olc::PixelGameEngine
{
public:
  PowderGame() { sAppName = "Powder Game"; }

private:
  air *   AIR;
  sand *  SAND;
  water * WATER;

  std::unique_ptr<air *[]> powders;
  int                      WIDTH;                   // Game World Width
  int                      HEIGHT;                  // Game World Height
  int                      powderSize       = 4;    // Size of a single Powder
  unsigned int             uBrushScale      = 1;
  bool                     bSimulate        = false;
  float                    fTargetFrameTime = 1.0f / 100.0f;    // Virtual FPS of 100fps
  float                    fAccumulatedTime = 0.0f;

public:
  bool OnUserCreate() override
  {
    WIDTH   = ScreenWidth() / powderSize;
    HEIGHT  = ScreenHeight() / powderSize;
    powders = std::make_unique<air *[]>( WIDTH * HEIGHT );
    AIR     = new air( olc::vi2d( WIDTH, HEIGHT ), powders.get() );
    SAND    = new sand( olc::vi2d( WIDTH, HEIGHT ), powders.get() );
    WATER   = new water( olc::vi2d( WIDTH, HEIGHT ), powders.get() );


    for( int y = 0; y < HEIGHT; y++ )
    {
      for( int x = 0; x < WIDTH; x++ )
      {
        powders[y * WIDTH + x] = AIR;
        if( x == 100 && y >= 95 && y < 105 ) powders[y * WIDTH + x] = SAND;
      }
    }

    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // Take user input
    if( GetMouse( 0 ).bHeld )    // Add sand on left click
    {
      fillPowderCircle( GetMouseX() / powderSize, GetMouseY() / powderSize, SAND, uBrushScale );
    }
    if( GetMouse( 0 ).bHeld && GetKey( olc::Key::CTRL ).bHeld )    // Add sand on left click
    {
      fillPowderCircle( GetMouseX() / powderSize, GetMouseY() / powderSize, WATER, uBrushScale );
    }
    if( GetMouse( 1 ).bHeld )    // Set to air on right click
    {
      fillPowderCircle( GetMouseX() / powderSize, GetMouseY() / powderSize, AIR, uBrushScale );
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
      for( int y = HEIGHT - 1; y >= 0; y-- )
      {
        for( int x = 0; x < WIDTH; x++ ) { powders[y * WIDTH + x]->update( x, y ); }
      }
    }
    // Clear the screen
    Clear( olc::VERY_DARK_GREY );

    // Draw in brush outline
    int scale = uBrushScale - 1, x = GetMouseX() / powderSize, y = GetMouseY() / powderSize;
    for( int i = -scale; i <= scale; i++ )
      for( int j = -scale; j <= scale; j++ )
        if( inRangeScreen( i + x, j + y ) && i * i + j * j <= scale * scale )
          FillRect( { ( i + x ) * powderSize, ( j + y ) * powderSize }, { powderSize, powderSize }, olc::CYAN );

    // Draw in powders
    for( int y = 0; y < HEIGHT; y++ )
    {
      for( int x = 0; x < WIDTH; x++ ) { powders[y * WIDTH + x]->draw( this, { x, y }, powderSize ); }
    }

    // If Paused display how to unpause on screen
    if( !bSimulate ) DrawString( 0, 0, "Press SPACE to Unpause", olc::WHITE );

    if( DEBUG )
    {
      // Debug Info
      DrawString( 0, 8, "Width: " + std::to_string( WIDTH ) + ", Height: " + std::to_string( HEIGHT ) );
      DrawString( 0,
                  16,
                  "Raw_Mouse_X: " + std::to_string( GetMouseX() ) + ", Raw_Mouse_Y: " + std::to_string( GetMouseY() ) );
      DrawString( 0,
                  24,
                  "Mouse_X: " + std::to_string( GetMouseX() / powderSize )
                      + ", Mouse_Y: " + std::to_string( GetMouseY() / powderSize ) );
    }

    // Display Brush Scale
    DrawString( 0, ScreenHeight() - 8, "Brush Scale: " + std::to_string( uBrushScale ), olc::WHITE );

    return true;
  }

  void fillPowderCircle( int x, int y, air * type, int scale )
  {
    scale--;
    for( int i = -scale; i <= scale; i++ )
      for( int j = -scale; j <= scale; j++ )
        if( inRange( i + x, j + y ) && i * i + j * j <= scale * scale ) powders[( j + y ) * WIDTH + ( i + x )] = type;
  }

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }
  bool inRangeScreen( int x, int y )
  {
    return ( x >= 0 ) && ( x < ScreenWidth() ) && ( y >= 0 ) && ( y < ScreenHeight() );
  }

  /*
  void moveSand( int x, int y )
  {
    // Check 3 positions and move accordingly

    if( y + 1 >= WIDTH ) return;

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
    if( y + 1 >= WIDTH ) return;

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
    if( powders[y * WIDTH + ( x - 1 )] == powderType::air && x - 1 >= 0 )
    {
      powders[y * WIDTH + ( x - 1 )] = type;
      powders[y * WIDTH + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderRight( int x, int y, powderType type )
  {
    if( powders[y * WIDTH + ( x + 1 )] == powderType::air && x + 1 < WIDTH )
    {
      powders[y * WIDTH + ( x + 1 )] = type;
      powders[y * WIDTH + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDown( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * WIDTH + x] == powderType::air )
    {
      powders[( y + 1 ) * WIDTH + x] = type;
      powders[y * WIDTH + x]         = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDownLeft( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * WIDTH + ( x - 1 )] == powderType::air && x - 1 >= 0 )
    {
      powders[( y + 1 ) * WIDTH + ( x - 1 )] = type;
      powders[y * WIDTH + x]                 = powderType::air;
      return true;
    }
    return false;
  }
  bool movePowderDownRight( int x, int y, powderType type )
  {
    if( powders[( y + 1 ) * WIDTH + ( x + 1 )] == powderType::air && x + 1 < WIDTH )
    {
      powders[( y - 1 ) * WIDTH + ( x + 1 )] = type;
      powders[y * WIDTH + x]                 = powderType::air;
      return true;
    }
    return false;
  }
  */
};

int main()
{
  PowderGame game;
  if( game.Construct( 800, 800, 1, 1 ) ) game.Start();
  return 0;
}