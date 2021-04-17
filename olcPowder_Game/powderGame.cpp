#define OLC_PGE_APPLICATION
#include <vector>

#include "powderGame.h"

int main()
{
  PowderGame game;
  if( game.Construct( 800, 800, 1, 1 ) ) game.Start();
  return 0;
}

inline bool PowderGame::OnUserCreate()
{
  WIDTH   = ScreenWidth() / powderSize;
  HEIGHT  = ScreenHeight() / powderSize;
  powders = std::make_unique<air *[]>( WIDTH * HEIGHT );
  AIR     = new air( olc::vi2d( WIDTH, HEIGHT ), powders.get() );
  SAND    = new sand( olc::vi2d( WIDTH, HEIGHT ), powders.get() );
  WATER   = new water( olc::vi2d( WIDTH, HEIGHT ), powders.get() );
  STONE   = new stone( olc::vi2d( WIDTH, HEIGHT ), powders.get() );

  powderTypes = { SAND, WATER, STONE };

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

inline bool PowderGame::OnUserUpdate( float fElapsedTime )
{
  takeUserInput();

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
  if( bSimulate ) { simulatePowders(); }

  drawScreen();

  return true;
}

inline void PowderGame::simulatePowders()
{
  // Update powders
  for( int y = HEIGHT - 1; y >= 0; y-- )
  {
    for( int x = 0; x < WIDTH; x++ ) { powders[y * WIDTH + x]->update( x, y ); }
  }
}

inline void PowderGame::fillPowderCircle( int x, int y, air * type, int scale, bool replace )
{
  scale--;
  for( int i = -scale; i <= scale; i++ )
    for( int j = -scale; j <= scale; j++ )
      if( inRange( i + x, j + y ) && i * i + j * j <= scale * scale )
      {
        if( replace || powders[( j + y ) * WIDTH + ( i + x )]->name == "air" )
        {
          powders[( j + y ) * WIDTH + ( i + x )] = type;
        }
      }
}

inline std::vector<int> PowderGame::countPowders()
{
  std::vector<int> counts = { 0, 0, 0 };

  for( int y = HEIGHT - 1; y >= 0; y-- )
  {
    for( int x = 0; x < WIDTH; x++ )
    {
      std::string name = powders[y * WIDTH + x]->name;
      if( name == "air" ) counts[0]++;
      else if( name == "sand" )
        counts[1]++;
      else if( name == "water" )
        counts[2]++;
    }
  }
  return counts;
}

void PowderGame::displayDebugInfo()
{
  // Debug Info
  DrawString( 1, 9, "Width: " + std::to_string( WIDTH ) + ", Height: " + std::to_string( HEIGHT ) );
  DrawString( 1,
              18,
              "Raw_Mouse_X: " + std::to_string( GetMouseX() ) + ", Raw_Mouse_Y: " + std::to_string( GetMouseY() ) );
  DrawString( 1,
              27,
              "Mouse_X: " + std::to_string( GetMouseX() / powderSize )
                  + ", Mouse_Y: " + std::to_string( GetMouseY() / powderSize ) );

  auto counts = countPowders();
  DrawString( 400, 1, "Air: " + std::to_string( counts[0] ) );
  DrawString( 400, 9, "Sand: " + std::to_string( counts[1] ) );
  DrawString( 400, 18, "Water: " + std::to_string( counts[2] ) );
}

inline void PowderGame::takeUserInput()
{
  // Take user input
  if( GetMouse( 0 ).bHeld )    // Fill a circle with selected powder
  {
    fillPowderCircle( GetMouseX() / powderSize,
                      GetMouseY() / powderSize,
                      powderTypes[selectedPowderIndex],
                      uBrushScale,
                      GetKey( olc::Key::CTRL ).bHeld );
  }
  if( GetMouse( 1 ).bHeld )    // Set to air on right click
  {
    fillPowderCircle( GetMouseX() / powderSize, GetMouseY() / powderSize, AIR, uBrushScale, true );
  }
  if( GetKey( olc::Key::SPACE ).bPressed ) { bSimulate = !bSimulate; }    // Pause and Unpause simulation
  if( GetKey( olc::Key::NP_ADD ).bPressed ) { uBrushScale++; }            // Enlarge the brush
  if( GetKey( olc::Key::NP_SUB ).bPressed )                               // Shrink the brush
  {
    uBrushScale--;
    if( uBrushScale < 1 ) uBrushScale = 1;
  }
  if( GetMouseWheel() > 0 )
  {
    selectedPowderIndex = ( selectedPowderIndex + 1 ) % numPowders;
  }    // Scroll up to increment selected powder
  if( GetMouseWheel() < 0 )
  {
    selectedPowderIndex = ( numPowders + ( ( selectedPowderIndex - 1 ) % numPowders ) ) % numPowders;
  }    // Scroll down to decrement selected powder
}

void PowderGame::drawScreen()
{
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
  if( !bSimulate ) DrawString( 1, 1, "Press SPACE to Unpause", olc::WHITE, 2 );

  if( DEBUG ) { displayDebugInfo(); }

  // Display Brush Scale
  DrawString( 1, ScreenHeight() - 33, "Brush Scale: " + std::to_string( uBrushScale ), olc::WHITE, 2 );

  // Display Selected Powder
  std::string selPowder = "Selected Powder: " + powderTypes[selectedPowderIndex]->name;
  DrawString( 1, ScreenHeight() - 16, selPowder, olc::WHITE, 2 );
}
