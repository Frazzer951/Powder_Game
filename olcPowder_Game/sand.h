#pragma once

#include "air.h"
#include "olcPixelGameEngine.h"
#include "powderGame.h"

class sand : public air
{
  sand( PowderGame * _game ) : air { _game } { name = "sand"; }

  virtual void update( int x, int y );
  virtual void draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize );
};
