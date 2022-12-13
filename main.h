
int level = 5;
int modelArray[100];
bool canTry = false;

void showGoodSeaquence()
{
  for (int i = 0; i < level; i++)
  {
    trellis.setPixelColor(modelArray[i], Wheel(map(modelArray[i], 0, X_DIM * Y_DIM, 0, 255)));
    trellis.show();
    delay(750);
  }
  delay(2000);
  for (int i = 0; i < level; i++)
  {
    trellis.setPixelColor(modelArray[i], 0);
  }
  trellis.show();
}
void newLevel()
{
  for (int i = 0; i < level; i++)
  {
    modelArray[i] = random(0, 63);
  }

  showGoodSeaquence();
  level++;
  canTry = true;
}
