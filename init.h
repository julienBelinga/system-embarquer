#include "Adafruit_NeoTrellis.h"
#define Y_DIM 8 // number of rows of key
#define X_DIM 8 // number of columns of keys

// create a matrix of trellis panels
Adafruit_NeoTrellis t_array[Y_DIM / 4][X_DIM / 4] = {

    {Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F)},

    {Adafruit_NeoTrellis(0x30), Adafruit_NeoTrellis(0x31)}

};

// pass this matrix to the multitrellis object
Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM / 4, X_DIM / 4);

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85)
  {
    return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

// define a callback for key presses
TrellisCallback blink(keyEvent evt)
{
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING)
    trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, X_DIM * Y_DIM, 0, 255))); // on rising
  else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING)
    trellis.setPixelColor(evt.bit.NUM, 0); // off falling

  trellis.show();
  return 0;
}
