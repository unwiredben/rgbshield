

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

#define NUM_FRAMES (12)

const char ediddy[NUM_FRAMES][16] = {{
0, 0, 0, 0,
0, 7, 7, 0,
0, 7, 7, 0,
0, 0, 0, 0,
},{ 
0, 7, 7, 0,
7, 6, 6, 7,
7, 6, 6, 7,
0, 7, 7, 0,
},{ 
7, 5, 5, 7,
5, 4, 4, 5,
5, 4, 4, 5,
7, 5, 5, 7,
},{ 
3, 3, 3, 3,
3, 2, 2, 3,
3, 2, 2, 3,
3, 3, 3, 3,
},{ 
2, 3, 3, 2,
3, 4, 4, 3,
3, 4, 4, 3,
2, 3, 3, 2,
},{ 
1, 3, 3, 1,
3, 6, 6, 3,
3, 6, 6, 3,
1, 3, 3, 1,
},{ 
2, 1, 1, 2,
1, 0, 0, 1,
1, 0, 0, 1,
2, 1, 1, 2,
},{ 
0, 1, 1, 0,
1, 0, 0, 1,
1, 0, 0, 1,
0, 1, 1, 0,
},{ 
0, 2, 2, 0,
2, 7, 7, 2,
2, 7, 7, 2,
0, 2, 2, 0,
},{ 
0, 4, 4, 0,
4, 5, 5, 4,
4, 5, 5, 4,
0, 4, 4, 0,
},{ 
7, 6, 6, 7,
6, 2, 2, 6,
6, 2, 2, 6,
7, 6, 6, 7,
},{ 
0, 7, 7, 0,
7, 5, 5, 7,
7, 5, 5, 7,
0, 7, 7, 0,
}};

// what order should we read the matrix to rotate by 0, 90, 180, and 270
const char rotation[4][16] = {
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
  { 3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12 },
  { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
  { 12, 8, 4, 0, 13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3 } 
};


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

void setMonoFrame(const char *frame, int r, int g, int b, int rotate = 0)
{
  for (char i = 0; i < 16; ++i)
  {
    char div = frame[rotation[rotate][i]];
    if (div > 0)
    {
      setRGB(i, r / div, g / div, b / div);
    }
  }
}

void setBWFrame(const char *frame, int r, int g, int b, int rotate = 0)
{
  for (char i = 0; i < 16; ++i)
  {
    char div = frame[rotation[rotate][i]];
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

  char rotation = random(4);

  for (char i = 0; i < NUM_FRAMES; ++i)
  {
    Tlc.setAll(0);
    setMonoFrame(ediddy[i], r, g, b, rotation);
    //setBWFrame(arrows[i], r, g, b);
    while(Tlc.update()) { }
    delay(DELAY_MS);
  }
}

void loop()
{
  arrowLoop();
}
