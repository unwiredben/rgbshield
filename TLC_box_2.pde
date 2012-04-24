

#include <Tlc5940.h>

#define DELAY_MS  (100)
#define MULT_LOW  (50)
#define MULT_HIGH (700)
#define DIV2 (3)
#define DIV3 (5)

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
  static char step = 0;
  static int r, g, b;
  int val;
  
  Tlc.setAll(0);

  if (step > 6) step = 0;

  switch (step++)
  {
  case 0:
    r = g = b = 0;
    
    val = random(MULT_HIGH - MULT_LOW) + MULT_LOW;
    switch (random(7))
    {
    case 0: r = val; break;
    case 1: g = val; break;
    case 2: b = val; break;
    case 3: r = g = val; break;
    case 4: g = b = val; break;
    case 5: b = r = val; break;
    case 6: r = g = b = val; break;
    }
    break;
    
  case 1: case 11:
    setInnerBox(r, g, b);
    break;
    
  case 2: case 10:
    setInnerBox(r / DIV2, g / DIV2, b / DIV2);
    setOuterBox(r, g, b);
    break;

  case 3: case 9:
    setInnerBox(r / DIV3, g / DIV3, b / DIV3);
    setOuterBox(r / DIV2, g / DIV2, b / DIV2);
    setCorners(r, g, b);
    break;

  case 4: case 8:
    setInnerBox(r / DIV3, g / DIV3, b / DIV3);
    setOuterBox(r / DIV2, g / DIV2, b / DIV2);
    setCorners(r, g, b);
    break;
    
  case 5: case 7:
    setOuterBox(r / DIV3, g / DIV3, b / DIV3);
    setCorners(r / DIV2, g / DIV2, b / DIV2);
    break;

  case 6:
    setCorners(r / DIV3, g / DIV3, b / DIV3);
    break;
  }
  
  Tlc.update();
  delay(DELAY_MS);
}

void loop()
{
  boxLoop();
}
