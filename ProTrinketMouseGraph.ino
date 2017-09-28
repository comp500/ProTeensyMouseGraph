int startX = -10; // maths units
int startY = 10; // maths units
float i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
int currentX = 0; // screen units
int currentY = 0; // screen units
float scaleFactor = 6.0;

void setup() {
  // no setup needed
}

void loop() {
  if (i == startX) {
    int halfHeight = height / 2;
    int halfWidth = width / 2;
    drawNext(0, halfHeight, false);
    downCursor();
    drawNext(0, halfHeight * -1, true);
    upCursor();
    drawNext(halfWidth * -1, 0, false);
    downCursor();
    drawNext(halfWidth, 0, true);
    upCursor();
    resetCursor();
  }

  if (i <= (width - startX)) {
    // (i*2, 10);
    drawNext(i, pow(i/2,2), true);
    //drawNext(i, i, true);
    i = i + (1 / scaleFactor);
  } else {
    i = startX;
    resetCursor();
    delay(4000);
  }
  delay(50);
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

void scaleCoords(float x, float y, int *resX, int *resY) {
  *resX = round((x - startX) * scaleFactor);
  *resY = round((y - startY) * scaleFactor * -1);
}

void deltaCoords(float x, float y, int *resX, int *resY) {
  *resX = x - currentX;
  *resY = y - currentY;
}

void calcCoords(float x, float y, int *resX, int *resY) {
  scaleCoords(x, y, resX, resY);
  deltaCoords(*resX, *resY, resX, resY);
  //currentX = currentX + *resX;
  //currentY = currentY + *resY;
}

void drawNext(float x, float y, boolean clickThrough) {
  if (checkValid(x, y)) {
    int normX;
    int normY;
    calcCoords(x, y, &normX, &normY);

    // Loops because it's a short
    int loopsX;
    int absLoopsX;
    if (normX == 0) {
      loopsX = 0;
      absLoopsX = 0;
    } else {
      float balanceX = normX > 0 ? 0.5 : -0.5;
      loopsX = round(normX / 127.0 + balanceX);
      absLoopsX = abs(loopsX);
    }

    int loopsY;
    int absLoopsY;
    if (normY == 0) {
      loopsY = 0;
      absLoopsY = 0;
    } else {
      float balanceY = normY > 0 ? 0.5 : -0.5;
      loopsY = round(normY / 127.0 + balanceY);
      absLoopsY = abs(loopsY);
    }

    int totalLoops = max(absLoopsX, absLoopsY);

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

      int leftButton = clickThrough ? 1 : 0;
      Mouse.set_buttons(leftButton, 0, 0);
      Mouse.move(normX, normY);

      currentX += moveX;
      currentY += moveY;
      //delay(200);
    }
  } else {
    upCursor(); // don't draw, reset cursor
  }
}

void upCursor() {
  Mouse.set_buttons(0, 0, 0);
  Mouse.move(0, 0);
}

void downCursor() {
  Mouse.set_buttons(1, 0, 0);
}
