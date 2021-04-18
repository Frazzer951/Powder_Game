#pragma once

#include "olcPixelGameEngine.h"
#include "powderGame.h"

struct air
{
  PowderGame * game;
  olc::vf2d    velocity = { 0, 0 };
  std::string  name     = "air";

  air( PowderGame * _game ) : game { _game } {}

  virtual void update( olc::vi2d pos, float fElapsedTime ) {}
  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize ) {}
};
