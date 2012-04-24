

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

#define NUM_FRAMES (9)

const char arrows[NUM_FRAMES][16] = {{ 
  0, 0, 0, 0,
  1, 0, 0, 0,
  1, 0, 0, 0,
  0, 0, 0, 0,
},{ 
  1, 0, 0, 0,
  1, 1, 0, 0,
  1, 1, 0, 0,
  1, 0, 0, 0,
},{ 
  3, 1, 0, 0,
  1, 1, 1, 1,
  1, 1, 1, 1,
  3, 1, 0, 0,
},{ 
  7, 3, 1, 0,
  1, 1, 1, 1,
  1, 1, 1, 1,
  7, 3, 1, 0,
},{ 
  0, 7, 3, 1,
  3, 1, 1, 1,
  3, 1, 1, 1,
  0, 7, 3, 1,
},{ 
  0, 0, 7, 3,
  7, 3, 1, 1,
  7, 3, 1, 1,
  0, 0, 7, 3,
},{ 
  0, 0, 0, 7,
  0, 7, 3, 1,
  0, 7, 3, 1,
  0, 0, 0, 7,
},{ 
  0, 0, 0, 0,
  0, 0, 7, 3,
  0, 0, 7, 3,
  0, 0, 0, 0,
},{ 
  0, 0, 0, 0,
  0, 0, 0, 7,
  0, 0, 0, 7,
  0, 0, 0, 0,
}};

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

void setMonoFrame(const char *frame, int r, int g, int b)
{
  for (char i = 0; i < 16; ++i)
  {
    char div = frame[i];
    if (div > 0)
    {
      setRGB(i, r / div, g / div, b / div);
    }
  }
}

void setBWFrame(const char *frame, int r, int g, int b)
{
  for (char i = 0; i < 16; ++i)
  {
    char div = frame[i];
    if (div == 1)
    {
      setRGB(i, r, g, b);
    }
  }
}

void arrowLoop()
{
  int r, g, b;
  int val;
  
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

  for (char i = 0; i < NUM_FRAMES; ++i)
  {
    Tlc.setAll(0);
    //setMonoFrame(arrows[i], r, g, b);
    setBWFrame(arrows[i], r, g, b);
    Tlc.update();
    delay(DELAY_MS);
  }
}

void loop()
{
  arrowLoop();
}
