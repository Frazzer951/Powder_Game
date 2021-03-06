#include "PowderGame.h"

#include "elements/Element.h"
#include "elements/EmptyCell.h"
#include "elements/Gas.h"
#include "elements/Liquid.h"
#include "elements/Sand.h"
#include "elements/Solid.h"
#include "elements/Stone.h"
#include "elements/Water.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

bool PowderGame::OnUserCreate()
{
  WIDTH            = ScreenWidth() / powderSize;
  HEIGHT           = ScreenHeight() / powderSize;
  iTargetFPS       = 60;
  fTargetFrameTime = 1.0f / iTargetFPS;

  powderTypes = { "Sand", "Stone", "Water" };
  num_powders = powderTypes.size();

  elements = std::make_unique<Element *[]>( WIDTH * HEIGHT );

  for( int y = 0; y < HEIGHT; y++ )
  {
    for( int x = 0; x < WIDTH; x++ )
    {
      Element * elem          = new EmptyCell( x, y );
      elements[y * WIDTH + x] = elem;
    }
  }

  return true;
}

bool PowderGame::OnUserUpdate( float fElapsedTime )
{
  takeUserInput();

  fAccumulatedTime += fElapsedTime;
  if( fAccumulatedTime >= fTargetFrameTime )
  {
    fAccumulatedTime -= fTargetFrameTime;
    fElapsedTime = fTargetFrameTime;
  }
  else
    return true;    // Don't do anything this frame

  // Only update the simulation if the game is not paused
  if( simulate )
  {
    // Update all elements
    for( int y = HEIGHT - 1; y >= 0; y-- )
    {
      for( int x = WIDTH - 1; x >= 0; x-- ) { elements[y * WIDTH + x]->update( this, fElapsedTime ); }
    }
  }
  updated = !updated;

  drawScreen();

  return true;
}

void PowderGame::swap( int x0, int y0, int x1, int y1 )
{
  Element * tmp             = elements[y0 * WIDTH + x0];
  elements[y0 * WIDTH + x0] = elements[y1 * WIDTH + x1];
  elements[y1 * WIDTH + x1] = tmp;
  elements[y0 * WIDTH + x0]->setPosition( x0, y0 );
  elements[y1 * WIDTH + x1]->setPosition( x1, y1 );
}

void PowderGame::swap( vec2i pos0, vec2i pos1 ) { swap( pos0.x, pos0.y, pos1.x, pos1.y ); }

Element * PowderGame::GetElementAt( int x, int y )
{
  if( inRange( x, y ) ) { return elements[y * WIDTH + x]; }
  else
  {
    return nullptr;
  }
}

void PowderGame::takeUserInput()
{
  int mouse_x = GetMouseX() / powderSize;
  int mouse_y = GetMouseY() / powderSize;
  // Take user input
  if( GetMouse( 0 ).bHeld )    // Fill a circle with selected powder
  {
    fillPowderCircle( mouse_x, mouse_y, powderTypes[selectedPowderIndex], BrushScale, GetKey( olc::Key::CTRL ).bHeld );
  }
  if( GetMouse( 1 ).bHeld )    // Set to Empty on right click
  {
    fillPowderCircle( mouse_x, mouse_y, "Empty", BrushScale, true );
  }
  if( GetKey( olc::Key::SPACE ).bPressed ) { simulate = !simulate; }    // Pause and Unpause simulation
  if( GetKey( olc::Key::NP_ADD ).bPressed ) { BrushScale++; }           // Enlarge the brush
  if( GetKey( olc::Key::NP_SUB ).bPressed )                             // Shrink the brush
  {
    BrushScale--;
    if( BrushScale < 1 ) BrushScale = 1;
  }
  if( GetMouseWheel() > 0 )
  {
    // Scroll up to increment selected powder
    selectedPowderIndex = selectedPowderIndex + 1;
  }
  if( GetMouseWheel() < 0 )
  {
    // Scroll down to decrement selected powder
    selectedPowderIndex = selectedPowderIndex - 1;
  }
  selectedPowderIndex = ( ( selectedPowderIndex % num_powders ) + num_powders ) % num_powders;
}

void PowderGame::fillPowderCircle( int x, int y, std::string type, int scale, bool replace )
{
  scale--;
  for( int i = -scale; i <= scale; i++ )
    for( int j = -scale; j <= scale; j++ )
      if( inRange( i + x, j + y ) && i * i + j * j <= scale * scale )
      {
        if( replace || dynamic_cast<EmptyCell *>( elements[( j + y ) * WIDTH + ( i + x )] ) )
        {
          delete elements[( j + y ) * WIDTH + ( i + x )];
          elements[( j + y ) * WIDTH + ( i + x )] = CreateElement( type );
          elements[( j + y ) * WIDTH + ( i + x )]->setPosition( i + x, j + y );
        }
      }
}

Element * PowderGame::CreateElement( std::string element_name )
{
  if( element_name == "Sand" ) { return new Sand( 0, 0 ); }
  if( element_name == "Stone" ) { return new Stone( 0, 0 ); }
  if( element_name == "Water" ) { return new Water( 0, 0 ); }
  if( element_name == "Empty" ) { return new EmptyCell( 0, 0 ); }
  return nullptr;
}

void PowderGame::drawScreen()
{
  // Clear the screen
  Clear( olc::VERY_DARK_GREY );

  // Draw in brush outline
  int scale = BrushScale - 1;
  int x     = GetMouseX() / powderSize;
  int y     = GetMouseY() / powderSize;

  for( int i = -scale; i <= scale; i++ )
    for( int j = -scale; j <= scale; j++ )
      if( inRangeScreen( i + x, j + y ) && i * i + j * j <= scale * scale )
        FillRect( { ( i + x ) * powderSize, ( j + y ) * powderSize }, { powderSize, powderSize }, olc::CYAN );

  // Draw in powders

  for( int x = 0; x < WIDTH; x++ )
  {
    for( int y = 0; y < HEIGHT; y++ )
    {
      int index = y * WIDTH + x;
      elements[index]->draw( this );
    }
  }

  // If Paused display how to unpause on screen
  if( !simulate ) DrawString( 1, 1, "Press SPACE to Unpause", olc::WHITE, 2 );

  // Display Brush Scale
  DrawString( 1, ScreenHeight() - 33, "Brush Scale: " + std::to_string( BrushScale ), olc::WHITE, 2 );

  // Display Selected Powder
  std::string selPowder = "Selected Powder: " + powderTypes[selectedPowderIndex];
  DrawString( 1, ScreenHeight() - 16, selPowder, olc::WHITE, 2 );
}
void PowderGame::DrawElement( int x, int y, olc::Pixel c )
{
  FillRect( { x * powderSize, y * powderSize }, { powderSize, powderSize }, c );
}
bool PowderGame::isEmpty( int x, int y ) { return dynamic_cast<EmptyCell *>( GetElementAt( x, y ) ) != nullptr; }
bool PowderGame::isLiquid( int x, int y ) { return dynamic_cast<Liquid *>( GetElementAt( x, y ) ) != nullptr; }
bool PowderGame::isSolid( int x, int y ) { return dynamic_cast<Solid *>( GetElementAt( x, y ) ) != nullptr; }
bool PowderGame::isGas( int x, int y ) { return dynamic_cast<Gas *>( GetElementAt( x, y ) ) != nullptr; }
void PowderGame::setElementAt( int x, int y, Element * element )
{
  elements[y * WIDTH + x] = element;
  elements[y * WIDTH + x]->setPosition( x, y );
}

int main()
{
  const int WIDTH  = 800;
  const int HEIGHT = 800;

  PowderGame pGame;
  if( pGame.Construct( WIDTH, HEIGHT, 1, 1 ) ) pGame.Start();

  return 0;
}