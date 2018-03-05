#include <unistd.h>
#include <cmath>
#include "gfx.h"

//********** Declaration ************//

class Asteroid;

class Point
{
  friend class Asteroid;
private:
  int x;
  int y;
public:
  Point (void);
  Point (const int&, const int&);
  int getX (void);
  int getY (void);
};

class Asteroid
{
private:
  size_t size;
  int rotation;
  const double pi = acos(-1);
  Point vertex[10];
  Point position;
  Point getVertex (const size_t&);
public:
  Asteroid (void);
  Asteroid (const int&, const int&, const size_t&);
  Asteroid (const Point&, const int&);
  int getX (void);
  int getY (void);
  void rotate (void);
  void draw (const int&);
};

//********** Definition ************//

Point::Point (void):
  x(0), y(0)
{

}

Point::Point (const int &x, const int &y):
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

Asteroid::Asteroid (void)
{
  
}

Asteroid::Asteroid (const int &x, const int &y, const size_t &size):
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
  for(int i=0;i<10;i++)
  {
    vertex[i].x = vertex[i].x*size;
    vertex[i].y = vertex[i].y*size;
  }
  rotation = -1;
}

Asteroid::Asteroid (const Point &p, const int &size):
  position (p),
  size (size)
{

}

Point 
Asteroid::getVertex (const size_t &index)
{
  if (index < 0 || index > 10)
  {
    return Point ();
  }
  int in;
  if( index > 9 )
  {
    in = 0;
  }
  else
  {
    in = index;
  }
  int
  xv = position.x + vertex[in].x ;
  int
  yv = position.y + vertex[in].y ;
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
  double angle = 5.0*(3/size);
  for ( size_t i = 0; i < 10; i++ )
  {
    int x = vertex[i].x;
    int y = vertex[i].y;
    vertex[i].x = ceil(x*cos( (angle/180)*pi)-y*sin( (angle/180)*pi));
    vertex[i].y = ceil(y*cos( (angle/180)*pi)+x*sin( (angle/180)*pi));
  }
}

void
Asteroid::draw (const int &frame)
{
  double speed = 6 / size;
  for (int i = 0; i < 10; i++)
  {
     gfx_line (frame * speed + getVertex (i).x,
	             frame * speed + getVertex (i).y,
               frame * speed + getVertex (i+1).x,
	             frame * speed + getVertex (i+1).y);
  }
  rotate();
}

//********** IMPLEMENTACION **********//

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int
main (int argc, char *argv[])
{
  if( argc < 2 )
  {
    cout << "\033[1;32masteroids:\033[0m \033[1;31mfatal error:\033[0m not enough arguments\nUsage:\n\tmain \e[4masteroid number\e[0m"<< endl;
    return 1;
  }
  int n = atoi (argv[1]);
  srand( time(NULL) );
  gfx_open (1440, 900, "Asteroids");
  gfx_color (0, 200, 100);
  vector<Asteroid> asteroid;
  for(int i=0;i < n;i++)
  {
    asteroid.push_back( Asteroid( rand()%1280+100, rand()%720+100, rand()%3+1 ) );
  }
  //Asteroid a (-100, -100, 3);
  
  for (int frame = 0; frame < 240; frame++)
    {
      gfx_clear ();
      for(int i = 0; i < asteroid.size(); i++)
      {
        asteroid.at(i).draw(frame);
      }
      //a.draw(frame);
      gfx_flush ();
      usleep (16000);
    }
  return 0;
}

