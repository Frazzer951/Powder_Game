#pragma once

#include "olcPixelGameEngine.h"

struct air
{
  const std::string name = "air";
  int               WIDTH;      // Game World Width
  int               HEIGHT;     // Game World Height
  air **            powders;    // Array of the game world

  air( olc::vi2d worldSize, air * world[] ) : WIDTH { worldSize.x }, HEIGHT { worldSize.y }, powders { world } {}

  virtual void update( int x, int y ) {}
  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize ) {}

  virtual bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }

  virtual void swap( olc::vi2d first, olc::vi2d second )
  {
    air * s1                             = powders[first.y * WIDTH + first.x];
    powders[first.y * WIDTH + first.x]   = powders[second.y * WIDTH + second.x];
    powders[second.y * WIDTH + second.x] = s1;
  }

  virtual bool movePowderLeft( int x, int y )
  {
    if( inRange( x - 1, y ) && powders[y * WIDTH + ( x - 1 )]->name == "air" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x - 1, y ) );
      return true;
    }
    return false;
  }

  virtual bool movePowderRight( int x, int y )
  {
    if( inRange( x + 1, y ) && powders[y * WIDTH + ( x + 1 )]->name == "air" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x + 1, y ) );
      return true;
    }
    return false;
  }

  virtual bool movePowderDown( int x, int y )
  {
    if( inRange( x, y + 1 ) && powders[( y + 1 ) * WIDTH + x]->name == "air" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x, y + 1 ) );
      return true;
    }
    return false;
  }

  virtual bool movePowderDownLeft( int x, int y )
  {
    if( inRange( x - 1, y + 1 ) && powders[( y + 1 ) * WIDTH + ( x - 1 )]->name == "air" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x - 1, y + 1 ) );
      return true;
    }
    return false;
  }

  virtual bool movePowderDownRight( int x, int y )
  {
    if( inRange( x + 1, y + 1 ) && powders[( y + 1 ) * WIDTH + ( x + 1 )]->name == "air" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x + 1, y + 1 ) );
      return true;
    }
    return false;
  }
};

struct sand : public air
{
  const std::string name = "sand";

  sand( olc::vi2d worldSize, air * world[] ) : air { worldSize, world } {}

  virtual void update( int x, int y )
  {
    // Check 3 positions and move accordingly
    if( movePowderDown( x, y ) ) return;

    bool bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderDownLeft( x, y ) ) return;
      if( movePowderDownRight( x, y ) ) return;
    }
    else
    {
      if( movePowderDownRight( x, y ) ) return;
      if( movePowderDownLeft( x, y ) ) return;
    }
  }

  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize )
  {
    pge->FillRect( { pos.x * powderSize, pos.y * powderSize },
                   { powderSize, powderSize },
                   olc::Pixel( 194, 178, 128 ) );
  }
};

struct water : public air
{
  const std::string name = "water";

  water( olc::vi2d worldSize, air * world[] ) : air { worldSize, world } {}

  virtual void update( int x, int y )
  {
    // Check 5 positions and move accordingly
    // Similar to sand, but will also move left and right
    if( movePowderDown( x, y ) ) return;

    bool bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderDownLeft( x, y ) ) return;
      if( movePowderDownRight( x, y ) ) return;
    }
    else
    {
      if( movePowderDownRight( x, y ) ) return;
      if( movePowderDownLeft( x, y ) ) return;
    }

    bRand = rand() % 2;

    if( bRand )
    {
      if( movePowderLeft( x, y ) ) return;
      if( movePowderRight( x, y ) ) return;
    }
    else
    {
      if( movePowderRight( x, y ) ) return;
      if( movePowderLeft( x, y ) ) return;
    }
  }

  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize )
  {
    pge->FillRect( { pos.x * powderSize, pos.y * powderSize }, { powderSize, powderSize }, olc::Pixel( 0, 0, 255 ) );
  }
};