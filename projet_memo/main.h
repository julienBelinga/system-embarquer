int level = 0;
int modelArray[100];
bool canTry = false;
int playerArray[64];
int playerTry = 0;

void showGoodSeaquence() {
  for (int i = 0; i < level; i++) {
    trellis.setPixelColor(modelArray[i], Wheel(map(modelArray[i], 0, X_DIM * Y_DIM, 0, 255)));
    trellis.show();
    delay(750);
  }
  delay(2000);
  for (int i = 0; i < level; i++) {
    trellis.setPixelColor(modelArray[i], 0);
  }
  trellis.show();
}
void newLevel() {
  for (int i = 0; i < level; i++) {
    modelArray[i] = random(0, 63);
  }

  showGoodSeaquence();

  level++;
  canTry = true;
}

void checkPlayerTry() {
  canTry = false;
  bool error = false;
  for (int i = 0; i < level; i++) {
    if (playerArray[i] != modelArray[i]) {
      trellis.setPixelColor(playerArray[i], (int)0xFF0000);
      trellis.setPixelColor(modelArray[i], (int)0x00FF00);
      error = true;
    } else {
      trellis.setPixelColor(playerArray[i], (int)0x00FF00);
    }
    trellis.show();
    delay(1000);
    trellis.setPixelColor(playerArray[i], (int)0x000000);
    trellis.setPixelColor(modelArray[i], (int)0x000000);
    if (error) {
      level = 0;
      for (int y = 0; y < Y_DIM; y++) {
        for (int x = 0; x < X_DIM; x++) {
          trellis.setPixelColor(x, y, 0x000000);
        }
      }
      trellis.show();
      canTry = false;
    }
  }
}