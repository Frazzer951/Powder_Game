#include "Element.h"
#include "PowderGame.h"


void Element::setPosition( vec2i new_pos ) { setPosition( new_pos.x, new_pos.y ); }
void Element::setPosition( int new_x, int new_y )
{
  pos.x = new_x;
  pos.y = new_y;
}