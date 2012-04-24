#include <Tlc5940.h>

void setup()
{
  Tlc.init();
}

int rPos = 0;
int gPos = 0;
int bPos = 0;
int ticks = 0;

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

void setInnerBox(int r, int g, int b)
{
  setXY(1, 1, r, g, b);
  setXY(1, 2, r, g, b);
  setXY(2, 1, r, g, b);
  setXY(2, 2, r, g, b);
}

void setCorners(int r, int g, int b)
{
  setXY(0, 0, r, g, b);
  setXY(0, 3, r, g, b);
  setXY(3, 0, r, g, b);
  setXY(3, 3, r, g, b);
}

void setOuterBox(int r, int g, int b)
{
  setXY(0, 1, r, g, b);
  setXY(0, 2, r, g, b);
  setXY(1, 0, r, g, b);
  setXY(1, 3, r, g, b);
  setXY(2, 0, r, g, b);
  setXY(2, 3, r, g, b);
  setXY(3, 1, r, g, b);
  setXY(3, 2, r, g, b);
}

void boxLoop()
{
  static char t = 0;
  static int R[3], G[3], B[3];
  R[2] = R[1]; G[2] = G[1]; B[2] = B[1];
  R[1] = R[0]; G[1] = G[0]; B[1] = B[0];
  R[0] =       G[0] =       B[0] = 0;
  if ((t++ & 7) == 0)
  {
    switch (0) // random(3))
    {
    case 0: R[0] = random(500); break;
    case 1: G[0] = random(500); break;
    case 2: B[0] = random(500); break;
    }
  }
  
  setInnerBox(R[0], G[0], B[0]);
  setOuterBox(R[1], G[1], B[1]);
  setCorners(R[2], G[2], B[2]);
}

void loop()
{
  Tlc.setAll(0);
  boxLoop();
  Tlc.update();
  delay(100);
}
