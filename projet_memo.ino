#include "Adafruit_NeoTrellis.h"
#include "init.h"
#include "main.h"
#define Y_DIM 8 // number of rows of key
#define X_DIM 8 // number of columns of keys


void setup()
{
  Serial.begin(9600);

  if (!trellis.begin())
  {
    Serial.println("failed to begin trellis");
    while (1)
      delay(1);
  }

  /* the array can be addressed as x,y or with the key number */
  for (int i = 0; i < Y_DIM * X_DIM; i++)
  {
    trellis.setPixelColor(i, Wheel(map(i, 0, X_DIM * Y_DIM, 0, 255))); // addressed with keynum
    trellis.show();
    delay(50);
  }

  for (int y = 0; y < Y_DIM; y++)
  {
    for (int x = 0; x < X_DIM; x++)
    {
      // activate rising and falling edges on all keys
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
      trellis.registerCallback(x, y, blink);
      trellis.setPixelColor(x, y, 0x000000); // addressed with x,y
      trellis.show();                        // show all LEDs
      delay(50);
    }
  }
  randomSeed(analogRead(0));
  newLevel();
}

void loop()
{
  trellis.read();
  delay(20);
}
