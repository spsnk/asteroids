#include <unistd.h>
#include "gfx.h"

//********** DECLARACION ************//

class Asteroid;

class Point
{
  friend class Asteroid;
  protected:
    int x;
    int y;
  public:
    Point ( void ) : x(0), y(0) { }
    Point ( int x, int y ): x(x), y(y) { }
    int getX ( void );
    int getY ( void );
};

class Asteroid
{
  private:
    size_t size;
    Point vertex[10];
    Point position;
    Point getVertex ( size_t );
  public:
    Asteroid ( int x, int y, size_t size ): position(Point(x,y)), size(size) { }
    Asteroid ( Point p, int size ): position(p), size(size) { }
    int getX ( void );
    int getY ( void );
    void draw ( int );
};

//********** DEFINICION ************//

int
Point::getX ( void )
{
  return x;
}

int 
Point::getY ( void )
{
  return y;
}

Point
Asteroid::getVertex ( size_t index )
{
  if(index < 0 || index > 10)
  {
    return Point();
  }
  int xv = position.x + vertex[index].x;
  xv *= size;
  int yv = position.y + vertex[index].y;
  yv *= size;
  return Point (xv, yv);
}

int
Asteroid::getX ( void )
{
  return position.getX();
}

int
Asteroid::getY ( void )
{
  return position.getY();
}

void
Asteroid::draw ( int time )
{
  //gfx_line( time*2+vertex[0], t*2+40, t*2+40, t*3+80 );
}

//********** IMPLEMENTACION **********//

int
main (int argc, char* argv[])
{
  return 0;
}
