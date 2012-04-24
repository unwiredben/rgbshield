/*
 * TLC_Chumbylight.pde
 *
 * Sketch to implement Arduino-side of Chumby "Ambilight" backlighting
 *
 * Ben Combee, January 2010
 */

#include <Tlc5940.h>

// no-cost stream operator as described at
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }


void setRGB(int pos, int r, int g, int b)
{
  Tlc.set(pos, r);
  Tlc.set(pos + 16, g);
  Tlc.set(pos + 32, b);
}

void setXY(int x, int y, int r, int g, int b)
{
  setRGB(x + (y * 4), r, g, b);
}

static int savedChar = -1;

int readBlocking()
{
  int ch;

  if (savedChar != -1) {
    ch = savedChar;
    savedChar = -1;
  } else {
    while (-1 == (ch = Serial.read())) { }
  }
  
  return ch;
}

int putBack(int ch)
{
  savedChar = ch;
}

int hex2dec(int ch)
{
  if (ch >= '0' && ch <= '9')
    return ch - '0';
  if (ch >= 'A' && ch <= 'F')
    return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f')
    return ch - 'a' + 10;
  return 0;
}

void setup()
{
  Serial.begin(38400);

  Tlc.init();
  // start all off
}

void loop()
{
  struct { int r, g, b; } quad[4];

  int ch;

  // find start of color marker
  while ((ch = readBlocking()) != 'Q') { }
  putBack(ch);
 
  for (int i = 0; i < 4; ++i)
  {
    readBlocking(); // absorb leading Q or dots between hex numbers
    quad[i].r = (hex2dec(readBlocking()) << 4) + hex2dec(readBlocking());
    quad[i].g = (hex2dec(readBlocking()) << 4) + hex2dec(readBlocking());
    quad[i].b = (hex2dec(readBlocking()) << 4) + hex2dec(readBlocking());
  }

  //Serial << quad[0].r << "," << quad[0].g << "," << quad[0].b << "\n";
  setXY(0, 0, quad[0].r, quad[0].g, quad[0].b);
  setXY(0, 1, quad[0].r, quad[0].g, quad[0].b);
  setXY(1, 0, quad[0].r, quad[0].g, quad[0].b);
  setXY(1, 1, quad[0].r, quad[0].g, quad[0].b);

  //Serial << quad[1].r << "," << quad[1].g << "," << quad[1].b << "\n";
  setXY(0, 2, quad[1].r, quad[1].g, quad[1].b);
  setXY(0, 3, quad[1].r, quad[1].g, quad[1].b);
  setXY(1, 2, quad[1].r, quad[1].g, quad[1].b);
  setXY(1, 3, quad[1].r, quad[1].g, quad[1].b);

  //Serial << quad[2].r << "," << quad[2].g << "," << quad[2].b << "\n";
  setXY(2, 0, quad[2].r, quad[2].g, quad[2].b);
  setXY(2, 1, quad[2].r, quad[2].g, quad[2].b);
  setXY(3, 0, quad[2].r, quad[2].g, quad[2].b);
  setXY(3, 1, quad[2].r, quad[2].g, quad[2].b);

  //Serial << quad[3].r << "," << quad[3].g << "," << quad[3].b << "\n";
  setXY(2, 2, quad[3].r, quad[3].g, quad[3].b);
  setXY(2, 3, quad[3].r, quad[3].g, quad[3].b);
  setXY(3, 2, quad[3].r, quad[3].g, quad[3].b);
  setXY(3, 3, quad[3].r, quad[3].g, quad[3].b);

  Tlc.update();
}
