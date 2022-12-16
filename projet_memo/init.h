#include "Adafruit_NeoTrellis.h"

#define Y_DIM 8 // number of rows of key
#define X_DIM 8 // number of columns of keys
#define DUREE_TEMPS 300
#define SILENCE 70

int tab[64];

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
void JouerNote(unsigned int note, unsigned int nombreDeTemps)
{
  tone(2, note, nombreDeTemps * DUREE_TEMPS);
}

// define a callback for key presses
TrellisCallback blink(keyEvent evt)
{
  if(!canTry){
    return 0;
  }

  if(playerTry <= level){
    playerArray[playerTry] = evt.bit.NUM;
    playerTry++;
  } 
  if(playerTry > level) {
    playerTry = 0;
    checkPlayerTry();
  }
  tab[0]= 62;
  tab[1]= 65;
  tab[2]= 73;
  tab[3]= 82;
  tab[4]= 87;
  tab[5]= 98;
  tab[6]= 110;
  tab[7]= 123;
  tab[8]= 131;
  tab[9]= 147;
  tab[10]= 165;
  tab[11]= 175;
  tab[12]= 196;
  tab[13]= 220;
  tab[14]= 247;
  tab[15]= 262;
  tab[16]= 294;
  tab[17]= 330;
  tab[18]= 349;
  tab[19]= 392;
  tab[20]= 440;
  tab[21]= 494;
  tab[22]= 523;
  tab[23]= 587;
  tab[24]= 659;
  tab[25]= 698;
  tab[26]= 784;
  tab[27]= 880;
  tab[28]= 988;
  tab[29]= 1047;
  tab[30]= 1175;
  tab[31]= 1319;
  tab[32]= 1397;
  tab[33]= 1568;
  tab[34]= 1760;
  tab[35]= 1976;
  tab[36]= 2093;
  tab[37]= 2349;
  tab[38]= 2637;
  tab[39]= 2794;
  tab[40]= 3136;
  tab[41]= 3520;
  tab[42]= 3951;
  tab[43]= 4186;
  tab[44]= 4699;
  tab[45]= 5274;
  tab[46]= 5587;
  tab[47]= 6272;
  tab[48]= 7040;
  tab[49]= 7902;
  tab[50]= 8372;
  tab[51]= 9397;
  tab[52]= 10548;
  tab[53]= 11175;
  tab[54]= 12544;
  tab[55]= 14080;
  tab[56]= 15804;
  tab[57]= 16744;
  tab[58]= 18795;
  tab[59]= 21096;
  tab[60]= 22351;
  tab[61]= 25088;
  tab[62]= 28160;
  tab[63]= 31609;
  JouerNote(tab[evt.bit.NUM], 1);
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING)
    trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, X_DIM * Y_DIM, 0, 255))); // on rising
  else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING)
    trellis.setPixelColor(evt.bit.NUM, 0); // off falling

  trellis.show();
  return 0;
}

