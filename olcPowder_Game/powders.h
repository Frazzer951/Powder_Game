#pragma once

#include "olcPixelGameEngine.h"
/*
struct air
{
  std::string name = "air";
  int         WIDTH;      // Game World Width
  int         HEIGHT;     // Game World Height
  air **      powders;    // Array of the game world

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
  sand( olc::vi2d worldSize, air * world[] ) : air { worldSize, world } { name = "sand"; }

  virtual void update( int x, int y )
  {
    // If water is below sand swap places
    if( inRange( x, y + 1 ) && powders[( y + 1 ) * WIDTH + x]->name == "water" )
    {
      swap( olc::vi2d( x, y ), olc::vi2d( x, y + 1 ) );
      return;
    }

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
  water( olc::vi2d worldSize, air * world[] ) : air { worldSize, world } { name = "water"; }

  virtual void update( int x, int y )
  {
    // Check 5 positions and move accordingly
    // Similar to sand, but will also move left and right
    if( movePowderDown( x, y ) ) return;    // Try moving down

    bool bRand = rand() % 2;    // Generate random bool

    if( bRand )    // Try moving down left or right
    {
      if( movePowderDownLeft( x, y ) ) return;
      if( movePowderDownRight( x, y ) ) return;
    }
    else
    {
      if( movePowderDownRight( x, y ) ) return;
      if( movePowderDownLeft( x, y ) ) return;
    }

    if( bRand )    // If there is an opening down left or right move towards it
    {
      if( openDownLeft( x, y ) )
        if( movePowderLeft( x, y ) ) return;
      if( openDownRight( x, y ) )
        if( movePowderRight( x, y ) ) return;
    }
    else
    {
      if( openDownRight( x, y ) )
        if( movePowderRight( x, y ) ) return;
      if( openDownLeft( x, y ) )
        if( movePowderLeft( x, y ) ) return;
    }

    if( bRand )    // Try moving left or right
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

  bool openDownLeft( int x, int y )
  {
    for( int i = x - 1; i >= 0; i-- )
    {
      if( !inRange( i, y + 1 ) ) break;
      if( powders[( y + 1 ) * WIDTH + i]->name == "air" ) return true;
    }
    return false;
  }

  bool openDownRight( int x, int y )
  {
    for( int i = x + 1; i < WIDTH; i++ )
    {
      if( !inRange( i, y + 1 ) ) break;
      if( powders[( y + 1 ) * WIDTH + i]->name == "air" ) return true;
    }
    return false;
  }
};

struct stone : public air
{
  stone( olc::vi2d worldSize, air * world[] ) : air { worldSize, world } { name = "stone"; }

  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize )
  {
    pge->FillRect( { pos.x * powderSize, pos.y * powderSize },
                   { powderSize, powderSize },
                   olc::Pixel( 136, 140, 141 ) );
  }
};*/