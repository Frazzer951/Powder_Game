#pragma once

#include "olcPixelGameEngine.h"
#include "powderGame.h"

struct air
{
private:
  PowderGame * game;
  olc::vf2d    velocity = { 0, 0 };

public:
  std::string name = "air";

  air( PowderGame * _game ) : game { _game } {}

  virtual void update( int x, int y ) {}
  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize ) {}
};
