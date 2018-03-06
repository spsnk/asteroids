#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include "gfx.h"

//********** Declaration ************//

class Asteroid;

class Point
{
  friend class Asteroid;
private:
  float x;
  float y;
public:
  Point (void);
  Point (const float&, const float&);
  float getX (void);
  float getY (void);
};

class Asteroid
{
private:
  size_t size;
  int rotation;
  int speed;
  float angle;
  const float pi = acos(-1);
  Point vertex[10];
  Point position;
  Point getVertex (const size_t&);
public:
  Asteroid (void);
  Asteroid (const int&, const int&, const size_t&);
  Asteroid (const Point&, const int&);
  float getX (void);
  float getY (void);
  void check_bounds (void);
  void rotate (void);
  void draw ();
};

//********** Definition ************//

Point::Point (void):
  x(0), y(0)
{

}

Point::Point (const float &x, const float &y):
  x(x), y(y)
{

}

float
Point::getX (void)
{
  return x;
}

float
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
  rotation = rand()%2==0?1:-1;
  speed = 6/size;
  angle = 1.0*(6/size);
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
  float
  xv = position.x + vertex[in].x ;
  float
  yv = position.y + vertex[in].y ;
  return Point (xv, yv);
}

float
Asteroid::getX (void)
{
  return position.getX ();
}

float
Asteroid::getY (void)
{
  return position.getY ();
}

void
Asteroid::rotate (void)
{
  for ( size_t i = 0; i < 10; i++ )
  {
    float x = vertex[i].x;
    float y = vertex[i].y;
    vertex[i].x = (x*cos( (angle/180)*pi) - (y*sin( (angle/180)*pi))*rotation );
    vertex[i].y = (y*cos( (angle/180)*pi) + (x*sin( (angle/180)*pi))*rotation );
  }
}

void
Asteroid::check_bounds (void)
{
  if( getX() > 1300 ) 
  {
    position.x = -20;
  }
  else if ( getX() < -20 )
  {
    position.x = 1300;
  }
  if( getY() > 740 )
  {
    position.y = -20;
  }
  else if ( getY() < -20 )
  {
    position.y = 740;
  }
}

void
Asteroid::draw (void)
{
  position.x += speed;
  position.y += speed;
  for (int i = 0; i < 10; i++)
  {
     gfx_line (getVertex (i).x,
	             getVertex (i).y,
               getVertex (i+1).x,
	             getVertex (i+1).y);
  }
  rotate();
  check_bounds();
}

//********** Implementation **********//

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
  gfx_open (1280, 720, "Asteroids");
  gfx_color (7, 242, 255);
  vector<Asteroid> asteroid;
  for(int i=0;i < n;i++)
  {
    asteroid.push_back( Asteroid( rand()%1280, rand()%720, rand()%3+1 ) );
  }
  clock_t begin;
  clock_t end;
  for (int frame = 0; frame <= 1000; frame++)
    {
      begin = clock();
      gfx_clear ();
      for(int i = 0; i < n; i++)
      {
        asteroid[i].draw();
      }
      gfx_flush ();
      end = clock();
      cout << frame << " frames drawn. Frame time: " << end-begin << '\r' << flush;
      usleep (16666);
    }
    cout << endl;
  return 0;
}

