#include <unistd.h>
#include <cmath>
#include "gfx.h"

//********** Declaration ************//

#define CW   1
#define CCW -1

class Asteroid;

class Point
{
  friend class Asteroid;
private:
  int x;
  int y;
public:
  Point (void);
  Point (int, int);
  int getX (void);
  int getY (void);
};

class Asteroid
{
private:
  size_t size;
  int rotation;
  Point vertex[10];
  Point position;
  Point getVertex (size_t);
public:
  Asteroid (int, int, size_t);
  Asteroid (Point, int);
  int getX (void);
  int getY (void);
  void rotate (void);
  void draw (int);
};

//********** Definition ************//

Point::Point (void):
  x(0), y(0)
{

}

Point::Point (int x, int y):
  x(x), y(y)
{

}

int
Point::getX (void)
{
  return x;
}

int
Point::getY (void)
{
  return y;
}

Asteroid::Asteroid (int x, int y, size_t size):
  position (Point (x, y)), size (size)
{
  vertex[0] = Point ( 1   , 25 );
  vertex[1] = Point ( 10  , 20 );
  vertex[2] = Point ( 20  , 10 );
  vertex[3] = Point ( 20  , -6 );
  vertex[4] = Point ( 15  ,-20 );
  vertex[5] = Point (  1  ,-15 );
  vertex[6] = Point (-12  ,-20 );
  vertex[7] = Point (-22  , -5 );
  vertex[8] = Point (-30  ,  5 );
  vertex[9] = Point (-25  , 15 );

  rotation = -1;
}

Asteroid::Asteroid (Point p, int size):
  position (p),
  size (size)
{

}

Point 
Asteroid::getVertex (size_t index)
{
  if (index < 0 || index > 10)
    {
      return Point ();
    }
  if( index > 9 )
  {
    index = 0;
  }
  int
  xv = position.x + vertex[index].x;
  xv *= size;
  int
  yv = position.y + vertex[index].y;
  yv *= size;
  return Point (xv, yv);
}

int
Asteroid::getX (void)
{
  return position.getX ();
}

int
Asteroid::getY (void)
{
  return position.getY ();
}

void
Asteroid::rotate ( void )
{
  double pi = acos(-1);
  double angle = 1.0*(5/size);
  for ( size_t i = 0; i < 10; i++ )
  {
    int x = vertex[i].x;
    int y = vertex[i].y;
    vertex[i].x = (int) round(x*cos(angle/180*pi)-y*sin(angle/180*pi));
    vertex[i].y = (int) round(y*cos(angle/180*pi)+x*sin(angle/180*pi));
  }
}

void
Asteroid::draw (int time)
{
  double speed = 6 / size;
  for (int i = 0; i < 10; i++)
  {
     gfx_line (time * speed + getVertex (i).x, time * speed + getVertex (i).y,
               time * speed + getVertex (i+1).x, time * speed + getVertex (i+1).y);
  }
  rotate();
}

//********** IMPLEMENTACION **********//

int
main (int argc, char *argv[])
{
  gfx_open (800, 600, "Asteroids");
  gfx_color (0, 200, 100);
  Asteroid a (0, 100, 3);
  Asteroid b (100, 0, 2);
  Asteroid c (0, 0, 1);

  for (int time = 0; time < 300; time++)
    {
      gfx_clear ();
      a.draw (time);
      b.draw (time);
      c.draw (time);
      gfx_flush ();
      usleep (16666);
    }
  return 0;
}
