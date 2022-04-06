#include "Element.h"
#include "PowderGame.h"

bool Element::actOnOther( Element * other ) { return false; }
void Element::moveToLastValid( PowderGame * pge, vec2i moveToLocation )
{
  if( moveToLocation.x == pos.x && moveToLocation.y == pos.y ) return;
  Element * toSwap = pge->GetElementAt( moveToLocation.x, moveToLocation.y );
  pge->swap( toSwap->pos, moveToLocation );
}
void Element::moveToLastValidAndSwap( PowderGame * pge, Element * toSwap, vec2i moveToLocation )
{
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