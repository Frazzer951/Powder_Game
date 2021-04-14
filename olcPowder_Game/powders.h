#pragma once

#include "olcPixelGameEngine.h"

struct air
{
  int WIDTH;     // Game World Width
  int HEIGHT;    // Game World Height

  air( olc::vi2d worldSize )
  {
    WIDTH  = worldSize.x;
    HEIGHT = worldSize.y;
  }

  virtual void update() {}
  virtual void draw( olc::PixelGameEngine * pge ) {}

  bool inRange( int x, int y ) { return ( x >= 0 ) && ( x < WIDTH ) && ( y >= 0 ) && ( y < HEIGHT ); }
  bool movePowderLeft( int x, int y ) { return false; }
  bool movePowderRight( int x, int y ) { return false; }
  bool movePowderDown( int x, int y ) { return false; }
  bool movePowderDownLeft( int x, int y ) { return false; }
  bool movePowderDownRight( int x, int y ) { return false; }
};