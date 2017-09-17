#include <ProTrinketMouse.h>

int startX = -10; // maths units
int startY = 10; // maths units
float i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
int currentX = 0; // screen units
int currentY = 0; // screen units
float scaleFactor = 1.0;

void setup() {
  TrinketMouse.begin();
}

void loop() {
  if (i == startX) {
    int halfHeight = height / 2;
    int halfWidth = width / 2;
    drawNext(halfWidth * -1, halfHeight * -1, false);
    downCursor();
    drawNext(halfWidth, halfHeight, true);
    delay(1000);
    drawNext(0, halfHeight, false);
    delay(1000);
    downCursor();
    drawNext(0, halfHeight * -1, true);
    delay(1000);
    resetCursor();
    delay(1000);
    drawNext(halfWidth * -1, 0, false);
    delay(1000);
    downCursor();
    drawNext(halfWidth, 0, true);
    delay(1000);
    resetCursor();
  }

  /*if (i <= (width - startX)) {
    // (i*2, 10);
    //drawNext(i*2, -10);
    //drawNext(i, i, true);
    i++;
  } else {
    i = startX;
    resetCursor();
    delay(1000);
  }*/
  delay(4000);
}

float compute(int x) {
  //return x;
  return pow(x,2);
}

void resetCursor() {
  upCursor();
  drawNext(startX, startY, false);
}

boolean checkValid(float x, float y) {
  int tempX = round(x) - startX;
  boolean testX = (tempX >= 0) && (tempX <= height);
  int tempY = round(y) + startY;
  boolean testY = (tempY >= 0) && (tempY <= height);
  return testX && testY;
}

void scaleCoords(float x, float y, int* resX, int* resY) {
  *resX = round((x - startX) * scaleFactor);
  *resY = round((y - startY) * scaleFactor * -1);
}

void deltaCoords(float x, float y, int* resX, int* resY) {
  *resX = x - currentX;
  *resY = y - currentY;
}

void calcCoords(float x, float y, int* resX, int* resY) {
  scaleCoords(x, y, resX, resY);
  deltaCoords(*resX, *resY, resX, resY);
  currentX = currentX + *resX;
  currentY = currentY + *resY;
}

void drawNext(float x, float y, boolean clickThrough) {
  if (checkValid(x, y)) {
    int mask = clickThrough ? MOUSEBTN_LEFT_MASK : 0;
    int* normXPtr;
    int* normYPtr;
    calcCoords(x, y, normXPtr, normYPtr);

    int normX = *normXPtr;
    int normY = *normYPtr;

    // Loops because it's a short
    int loopsX = ceil(normX / 127.0);
    int loopsY = ceil(normY / 127.0);
    int totalLoops = abs(loopsX) + abs(loopsY);

    for (int j = 0; j < totalLoops; j++) {
      int moveX = 0;
      int moveY = 0;
      if (loopsX != 0) {
        if (loopsX < 0) {
          if (loopsX == -1) {
            moveX = normX;
          } else {
            normX = normX + 127;
            moveX = -127;
          }
          loopsX++;
        } else {
          if (loopsX == 1) {
            moveX = normX;
          } else {
            normX = normX - 127;
            moveX = 127;
          }
          loopsX--;
        }
      }
      if (loopsY != 0) {
        if (loopsY < 0) {
          if (loopsY == -1) {
            moveY = normY;
          } else {
            normY = normY + 127;
            moveY = -127;
          }
          loopsY++;
        } else {
          if (loopsY == 1) {
            moveY = normY;
          } else {
            normY = normY - 127;
            moveY = 127;
          }
          loopsY--;
        }
      }
      TrinketMouse.move(normX, normY, 0, mask);
    }
  } else {
    TrinketMouse.move(0, 0, 0, 0); // don't draw, reset cursor
  }
}

void upCursor() {
  TrinketMouse.move(0, 0, 0, 0); // reset cursor
}

void downCursor() {
  TrinketMouse.move(0, 0, 0, MOUSEBTN_LEFT_MASK);
}
