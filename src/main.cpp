#include "PowderGame.h"

#include "elements/Air.h"
#include "elements/Element.h"
#include "elements/EmptyCell.h"
#include "elements/Sand.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

bool PowderGame::OnUserCreate()
{
  WIDTH            = ScreenWidth();
  HEIGHT           = ScreenHeight();
  iTargetFPS       = 60;
  fTargetFrameTime = 1.0f / iTargetFPS;


  elements = std::make_unique<Element *[]>( WIDTH * HEIGHT );

  for( int y = 0; y < HEIGHT; y++ )
  {
    for( int x = 0; x < WIDTH; x++ )
    {
      if( ( x >= 100 && x <= 120 ) && ( y >= 100 && y <= 120 ) )
      {
        Sand * elem             = new Sand( x, y );
        elements[y * WIDTH + x] = elem;
      }
      else
      {
        Element * elem          = new EmptyCell( x, y );
        elements[y * WIDTH + x] = elem;
      }
    }
  }

  return true;
}

bool PowderGame::OnUserUpdate( float fElapsedTime )
{
  fAccumulatedTime += fElapsedTime;
  if( fAccumulatedTime >= fTargetFrameTime )
  {
    fAccumulatedTime -= fTargetFrameTime;
    fElapsedTime = fTargetFrameTime;
  }
  else
    return true;    // Don't do anything this frame

  // Update all elements
  for( int y = HEIGHT - 1; y >= 0; y-- )
  {
    for( int x = WIDTH - 1; x >= 0; x-- ) { elements[y * WIDTH + x]->update( this ); }
  }

  Clear( olc::BLACK );

  for( int x = 0; x < WIDTH; x++ )
  {
    for( int y = 0; y < HEIGHT; y++ )
    {
      int index = y * WIDTH + x;
      elements[index]->draw( this );
    }
  }
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

Element * PowderGame::GetElementAt( int x, int y ) { return elements[y * WIDTH + x]; }
bool      PowderGame::InRange( int x, int y ) { return ( x >= 0 && x < WIDTH ) && ( y >= 0 && y < HEIGHT ); }


int main()
{
  const int WIDTH  = 240;
  const int HEIGHT = 240;

  PowderGame pGame;
  if( pGame.Construct( WIDTH, HEIGHT, 4, 4 ) ) pGame.Start();

  return 0;
}