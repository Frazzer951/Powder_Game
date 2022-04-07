#include "Element.h"
#include "PowderGame.h"

bool Element::actOnOther( Element * other ) { return false; }
void Element::moveToLastValid( PowderGame * pge, vec2i lastValid )
{
  if( lastValid.x == pos.x && lastValid.y == pos.y ) return;
  pge->swap( pos, lastValid );
}
void Element::moveToLastValidAndSwap( PowderGame * pge, Element * toSwap, vec2i moveToLocation )
{
  // TODO: Redo this function
  // First goto last valid, then swap with toSwap
  int       x     = moveToLocation.x;
  int       y     = moveToLocation.y;
  Element * third = pge->GetElementAt( x, y );
  if( third == this || third == toSwap )
  {
    pge->swap( pos, toSwap->getPos() );
    return;
  }
  if( this == toSwap )
  {
    pge->swap( pos, moveToLocation );
    return;
  }

  pge->setElementAt( pos, third );
  pge->setElementAt( toSwap->getPos(), this );
  pge->setElementAt( moveToLocation, toSwap );
}
void Element::setPosition( vec2i new_pos ) { setPosition( new_pos.x, new_pos.y ); }
void Element::setPosition( int new_x, int new_y )
{
  pos.x = new_x;
  pos.y = new_y;
}