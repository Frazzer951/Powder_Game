#include "sand.h"

void sand::update( olc::vi2d pos, float fElapsedTime )
{
  velocity.y = game->clamp( velocity.y + ( game->gravity * fElapsedTime ), -10, 10 );

  if( game->inRange( pos.x, pos.y + 1 ) && game->getParticleAt( pos.x, pos.y + 1 )->name != "air"
      && game->getParticleAt( pos.x, pos.y + 1 )->name != "water" )
  {
    velocity.y /= 2.0f;
  }

  olc::vi2d wantedPos = pos + velocity;
}

void sand::draw( olc::PixelGameEngine * pge, olc::vi2d pos, int powderSize )
{
  pge->FillRect( { pos.x * powderSize, pos.y * powderSize }, { powderSize, powderSize }, olc::Pixel( 194, 178, 128 ) );
}