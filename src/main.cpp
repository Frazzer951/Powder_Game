#include "PowderGame.h"

#include "elements/Air.h"
#include "elements/Element.h"
#include "elements/Sand.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"


bool PowderGame::OnUserCreate()
{
  WIDTH    = ScreenWidth();
  HEIGHT   = ScreenHeight();
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
        Air * elem              = new Air( x, y );
        elements[y * WIDTH + x] = elem;
      }
    }
  }

  return true;
}

bool PowderGame::OnUserUpdate( float fElapsedTime )
{
  // called once per frame
  for( int x = 0; x < WIDTH; x++ )
  {
    for( int y = 0; y < HEIGHT; y++ )
    {
      int index = y * WIDTH + x;
      elements[index]->update( this );
      elements[index]->draw( this );
    }
  }
  return true;
}

Element * PowderGame::GetElementAt( int x, int y ) { return elements[y * WIDTH + x]; }


int main()
{
  const int WIDTH  = 240;
  const int HEIGHT = 240;

  PowderGame pGame;
  if( pGame.Construct( WIDTH, HEIGHT, 4, 4 ) ) pGame.Start();

  return 0;
}