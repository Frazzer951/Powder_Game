#ifndef POWDERGAME_POWDERGAME_H
#define POWDERGAME_POWDERGAME_H

#include <ctime>
#include <string>
#include <vector>

#include "vec2.h"

#include "elements/Element.h"

#include "olcPixelGameEngine/olcPixelGameEngine.h"

class PowderGame : public olc::PixelGameEngine
{
private:
  std::unique_ptr<Element *[]> elements;
  std::vector<std::string>     powderTypes;
  int                          WIDTH;     // Game World Width
  int                          HEIGHT;    // Game World Height
  int                          num_powders;
  int                          powderSize          = 4;    // Size of a single Powder
  int                          selectedPowderIndex = 0;
  unsigned int                 BrushScale          = 1;
  int                          iTargetFPS;
  float                        fTargetFrameTime;
  float                        fAccumulatedTime = 0.0f;
  bool                         simulate         = false;
  bool                         updated;
  vec2f                        gravity = vec2f( 0.0f, 5.0f );

public:
  PowderGame()
  {
    sAppName = "Powder Game";
    std::srand( std::time( nullptr ) );
  }

  bool      OnUserCreate() override;
  bool      OnUserUpdate( float fElapsedTime ) override;
  void      swap( int x0, int y0, int x1, int y1 );
  void      swap( vec2i pos0, vec2i pos1 );
  void      takeUserInput();
  void      drawScreen();
  void      DrawElement( int x, int y, olc::Pixel c );
  Element * GetElementAt( int x, int y );
  Element * CreateElement( std::string element_name );
  int       rand2() { return std::rand() % 2; }
  int       rand( int from, int to ) { return std::rand() % ( to - from ) + from; }
  void      PowderGame::fillPowderCircle( int x, int y, std::string type, int scale, bool replace );
  bool      isUpdated() const { return updated; }
  bool      isEmpty( int x, int y );
  bool      isLiquid( int x, int y );
  bool      isSolid( int x, int y );
  bool      isGas( int x, int y );
  bool      isEmpty( vec2i pos ) { return isEmpty( pos.x, pos.y ); }
  bool      isLiquid( vec2i pos ) { return isLiquid( pos.x, pos.y ); }
  bool      isSolid( vec2i pos ) { return isSolid( pos.x, pos.y ); }
  bool      isGas( vec2i pos ) { return isGas( pos.x, pos.y ); }
  void      setElementAt( int x, int y, Element * element );
  void      setElementAt( vec2i pos, Element * element ) { setElementAt( pos.x, pos.y, element ); }

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }
  bool inRangeScreen( int x, int y )
  {
    return ( x >= 0 ) && ( x < ScreenWidth() ) && ( y >= 0 ) && ( y < ScreenHeight() );
  }
  vec2f getGravity() { return gravity; }
};


#endif    // POWDERGAME_POWDERGAME_H
