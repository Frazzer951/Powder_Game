#include "elements/Air.h"
#include "elements/Element.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame : public olc::PixelGameEngine
{
private:
  std::unique_ptr<Element *[]> elements;
  int                          WIDTH;
  int                          HEIGHT;

public:
  PowderGame() { sAppName = "PowderGame"; }

public:
  bool OnUserCreate() override
  {
    WIDTH    = ScreenWidth();
    HEIGHT   = ScreenHeight();
    elements = std::make_unique<Element*[]>( WIDTH * HEIGHT );

    for( int y = 0; y < HEIGHT; y++ )
    {
      for( int x = 0; x < WIDTH; x++ )
      {
        Air* elem = new Air(x,y);
        elements[y * WIDTH + x] = elem;
      }
    }

    return true;
  }

  bool OnUserUpdate( float fElapsedTime ) override
  {
    // called once per frame
    for( int x = 0; x < WIDTH; x++ )
    {
      for( int y = 0; y < HEIGHT; y++ )
      {
        int index = y * WIDTH + x;
        elements[index]->update();
        elements[index]->draw( this );
      }
    }
    return true;
  }
};


int main()
{
  const int WIDTH  = 240;
  const int HEIGHT = 240;

  PowderGame pGame;
  if( pGame.Construct( WIDTH, HEIGHT, 4, 4 ) ) pGame.Start();

  return 0;
}