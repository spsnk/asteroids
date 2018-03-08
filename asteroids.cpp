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
  Point vertex[10];
  Point position;
  Point direction;
  Point getVertex (const size_t&);
public:
  Asteroid (void);
  Asteroid (const int&, const int&, const size_t&);
  float getX (void);
  float getY (void);
  void check_bounds (void);
  void rotate (void);
  void draw ();
};


const int shape [8][10][2] =
{
  { {0,20},{10,15},{20,5},{20,-10},{15,-25},{0,-20},{-10,-25},{-20,-10},{-30,0},{-25,10} },
  { {3,11},{13,6},{18,-4},{13,-9},{8,-14},{3,-11},{-12,-9},{-17,0},{-12,11},{0,13} },
  { {5,20},{10,15},{15,0},{10,-10},{5,-25},{-10,-15},{-15,-5},{-5,10},{-10,20},{0,30} },
  { {-3,13},{13,15},{17,7},{15,-6},{4,-12},{-19,-5},{-19,2},{-15,7},{-11,5},{-7,4} },
  { {-10,20},{5,5},{20,0},{20,-10},{5,-20},{-10,-15},{-15,0},{-30,5},{-25,15},{-15,15} },
  { {30,30},{40,20},{30,0},{30,-20},{-10,-40},{-30,-30},{-40,10},{-40,20},{-18,29},{0,40} },
  { {-25,10},{-15,30},{5,40},{15,20},{25,0},{15,-20},{-5,-40},{-25,-30},{-15,-10},{-25,0} },
  { {-12,8},{-14,-14},{-7,-24},{11,-27},{15,-14},{13,0},{15,15},{10,25},{-4,28},{-14,15} }
};

const float pi = acos(-1);

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
  int d = rand()%8;
  for(size_t i = 0; i < 10 ; i++)
  {
    int x = shape[d][i][0] * size;
    int y = shape[d][i][1] * size;
    vertex[i] = Point ( x, y );
  }
  rotation = rand()%2==0?1:-1;
  speed = 4 - size;
  angle = 0.5*(6.0/size);
  direction = Point (rand()%5-2, rand()%5-2);
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
  position.x += speed*direction.getX();
  position.y += speed*direction.getY();
  for (int i = 0; i < 10; i++)
  {
    gfx_line (getVertex (i).x, getVertex (i).y,
              getVertex (i+1).x, getVertex (i+1).y);
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
    cout << "\033[1;32masteroids:\033[0m \033[1;31mfatal error:\033[0m not enough arguments\nUsage:\n\t\033[1;32masteroids:\033[0m \e[4masteroid number\e[0m"<< endl;
    return 1;
  }
  int n = atoi (argv[1]);
  srand( time(NULL) );
  gfx_open (1280, 720, "Asteroids");
  gfx_color (7, 242, 255);
  vector<Asteroid> asteroid;
  for(int i=0; i < n; i++)
  {
    asteroid.push_back( Asteroid( rand()%1280, rand()%720, rand()%3+1 ) );
  }
  clock_t begin;
  clock_t end;
  cout.precision(6);
  cout << fixed;
  for (int frame = 0; true ; frame++)
  {
    begin = clock();
    gfx_clear ();
    for(int i = 0; i < n; i++)
    {
      asteroid[i].draw();
    }
    gfx_flush ();
    end = clock();
    cout << frame << " frames drawn. Frame time: " << ((float)end-begin)/CLOCKS_PER_SEC << "s\r" << flush;
    usleep (16666);
  }
  cout << endl;
  return 0;
}

