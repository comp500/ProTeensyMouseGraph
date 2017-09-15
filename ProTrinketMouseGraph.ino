#include <ProTrinketMouse.h>

int startX = -10; // maths units
int startY = 10; // maths units
int i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
int currentX = 0; // screen units
int currentY = 0; // screen units
float scaleFactor = 10.0;

void setup() {
  TrinketMouse.begin();
}

void loop() {
  if (!checkX(i)) {
    TrinketMouse.move(0, 0, 0, 0); // reset movement
    TrinketMouse.move((-1 * currentX), (-1 * currentY), 0, 0);
    currentX = 0;
    currentY = 0;
    i = startX;
    delay(8000);
  } else {
    float newY = compute(i);
    if (checkY(newY)) {
      int normalizedX = normalizeX(i);
      int normalizedY = normalizeY(newY);

      currentX += normalizedX;
      currentY += normalizedY;
      TrinketMouse.move(normalizedX, normalizedY, 0, MOUSEBTN_LEFT_MASK);
    }
    i++;
    delay(50);
  }
}

boolean checkX(float x) {
  int tempX = round(x) - startX;
  return (tempX >= 0) && (tempX <= height);
}

boolean checkY(float y) {
  int tempY = round(y) + startY;
  return (tempY >= 0) && (tempY <= height);
}

int normalizeX(float x) {
  int scaledX = round((x + startX) * scaleFactor);
  int result = scaledX - currentX;
  return result;
}

int normalizeY(float y) {
  int scaledY = round((y - startY) * scaleFactor * -1);
  int result = scaledY - currentY;
  return result;
}

float compute(int x) {
  //return x;
  return pow(x,2);
}

void drawNext(float x, float y) {

}

void moveCursor(float x, float y) {

}

boolean checkValid(float x, float y) {
  int tempX = round(x) - startX;
  boolean testX = (tempX >= 0) && (tempX <= height);
}

void scaleCoords(float x, float y, int &resX, int &resY) {

}

