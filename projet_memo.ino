#include "Adafruit_NeoTrellis.h"

#define Y_DIM 8  // number of rows of key
#define X_DIM 8  // number of columns of keys
#define DUREE_TEMPS 300
#define SILENCE 70

int tab[64];
int level;
int modelArray[64];
bool canTry = false;
int playerArray[64];
int playerTry;
// create a matrix of trellis panels
Adafruit_NeoTrellis t_array[Y_DIM / 4][X_DIM / 4] = {

  { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F) },

  { Adafruit_NeoTrellis(0x30), Adafruit_NeoTrellis(0x31) }

};

// pass this matrix to the multitrellis object
Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM / 4, X_DIM / 4);

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}
void JouerNote(unsigned int note, unsigned int nombreDeTemps) {
  tone(2, note, nombreDeTemps * DUREE_TEMPS);
}


//check if player sequence is right
void checkPlayerTry() {
  canTry = false;
  bool error = false;
  for (int i = 0; i < level; i++) {
    //Serial.print("player seq ");
    //Serial.println(playerArray[i]);
    //Serial.print("model seq ");
    //Serial.println(modelArray[i]);
    if (playerArray[i] != modelArray[i]) {
      //Serial.println("different");
      trellis.setPixelColor(playerArray[i], (int)0xFF0000);
      trellis.setPixelColor(modelArray[i], (int)0x00FF00);
      error = true;
    } else {
      //Serial.println("good");
      trellis.setPixelColor(playerArray[i], (int)0x00FF00);
    }
    trellis.show();
    delay(1000);
    trellis.setPixelColor(playerArray[i], (int)0x000000);
    trellis.setPixelColor(modelArray[i], (int)0x000000);
  }
  if (error) {
    level = 0;
    for (int y = 0; y < Y_DIM; y++) {
      for (int x = 0; x < X_DIM; x++) {
        trellis.setPixelColor(x, y, 0xFF0000);
      }
    }
    trellis.show();
    delay(2000);
    for (int y = 0; y < Y_DIM; y++) {
      for (int x = 0; x < X_DIM; x++) {
        trellis.setPixelColor(x, y, 0xFF0000);
      }
    }
    trellis.show();
    delay(1000);
    canTry = false;
  } else
  delay(1000);
  newLevel();
}

void showGoodSeaquence() {
  for (int i = 0; i <= level; i++) {
    trellis.setPixelColor(modelArray[i], Wheel(map(modelArray[i], 0, X_DIM * Y_DIM, 0, 255)));
    trellis.show();
    delay(750);
  }
  delay(2000);
  for (int i = 0; i <= level; i++) {
    trellis.setPixelColor(modelArray[i], 0);
  }
  trellis.show();
}
void newLevel() {
  //Serial.print("level ");
  //Serial.println(level);
  for (int i = 0; i <= level; i++) {
    modelArray[i] = random(0, 63);
  }

  showGoodSeaquence();

playerTry = 0;
  level++;
  canTry = true;
}

// define a callback for key presses
TrellisCallback blink(keyEvent evt) {
  if (!canTry) {
    return 0;
  }

  
  tab[0] = 62;
  tab[1] = 65;
  tab[2] = 73;
  tab[3] = 82;
  tab[4] = 87;
  tab[5] = 98;
  tab[6] = 110;
  tab[7] = 123;
  tab[8] = 131;
  tab[9] = 147;
  tab[10] = 165;
  tab[11] = 175;
  tab[12] = 196;
  tab[13] = 220;
  tab[14] = 247;
  tab[15] = 262;
  tab[16] = 294;
  tab[17] = 330;
  tab[18] = 349;
  tab[19] = 392;
  tab[20] = 440;
  tab[21] = 494;
  tab[22] = 523;
  tab[23] = 587;
  tab[24] = 659;
  tab[25] = 698;
  tab[26] = 784;
  tab[27] = 880;
  tab[28] = 988;
  tab[29] = 1047;
  tab[30] = 1175;
  tab[31] = 1319;
  tab[32] = 1397;
  tab[33] = 1568;
  tab[34] = 1760;
  tab[35] = 1976;
  tab[36] = 2093;
  tab[37] = 2349;
  tab[38] = 2637;
  tab[39] = 2794;
  tab[40] = 3136;
  tab[41] = 3520;
  tab[42] = 3951;
  tab[43] = 4186;
  tab[44] = 4699;
  tab[45] = 5274;
  tab[46] = 5587;
  tab[47] = 6272;
  tab[48] = 7040;
  tab[49] = 7902;
  tab[50] = 8372;
  tab[51] = 9397;
  tab[52] = 10548;
  tab[53] = 11175;
  tab[54] = 12544;
  tab[55] = 14080;
  tab[56] = 15804;
  tab[57] = 16744;
  tab[58] = 18795;
  tab[59] = 21096;
  tab[60] = 22351;
  tab[61] = 25088;
  tab[62] = 28160;
  tab[63] = 31609;
  JouerNote(tab[evt.bit.NUM], 1);
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING){
    trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, X_DIM * Y_DIM, 0, 255)));  // on rising
}
  else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING){
    trellis.setPixelColor(evt.bit.NUM, 0);  // off falling
    playerArray[playerTry] = evt.bit.NUM;
playerTry++;
  if (playerTry >= level) {
    delay(1000);
    playerTry = 0;
    checkPlayerTry();
  }
  //Serial.println(playerTry);
  }
  trellis.show();
 
  return 0;
}

void setup() {
  Serial.begin(9600);

  if (!trellis.begin()) {
    Serial.println("failed to begin trellis");
    while (1)
      delay(1);
  }

  /* the array can be addressed as x,y or with the key number */
  for (int i = 0; i < Y_DIM * X_DIM; i++) {
    trellis.setPixelColor(i, Wheel(map(i, 0, X_DIM * Y_DIM, 0, 255)));  // addressed with keynum
    trellis.show();
    delay(10);
  }

  for (int y = 0; y < Y_DIM; y++) {
    for (int x = 0; x < X_DIM; x++) {
      // activate rising and falling edges on all keys
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
      trellis.registerCallback(x, y, blink);
      trellis.setPixelColor(x, y, 0x000000);  // addressed with x,y
      trellis.show();                         // show all LEDs
      delay(10);
    }
  }
  randomSeed(analogRead(0));
  level = 0;
  newLevel();
}

void loop() {
  trellis.read();
  delay(20);
}
