//
// Created by CAD Station 2 on 4/5/2022.
//

#ifndef POWDERGAME_COLOR_H
#define POWDERGAME_COLOR_H


class Color
{
private:
  int _r;
  int _g;
  int _b;

public:
  Color( int r, int g, int b ) : _r( r ), _g( g ), _b( b ) {}
  int  R() const { return _r; }
  void R( int r ) { Color::_r = r; }
  int  G() const { return _g; }
  void G( int g ) { Color::_g = g; }
  int  B() const { return _b; }
  void B( int b ) { Color::_b = b; }
};


#endif    // POWDERGAME_COLOR_H
