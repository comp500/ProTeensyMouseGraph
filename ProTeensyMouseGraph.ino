int startX = -10; // maths units
int startY = 10; // maths units
int i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
boolean justReset = false;

void setup() {
  Mouse.screenSize(40, 40);
  Serial.begin(115200);
  Serial.println("Hi");
  delay(3000);
}

void loop() {
  if (i == startX) {
    int halfHeight = height / 2;
    int halfWidth = width / 2;
    Mouse.moveTo(halfWidth, 0);
    //Mouse.set_buttons(1, 0, 0);
    delay(50);
    Mouse.moveTo(halfWidth, height);
    //Mouse.set_buttons(0, 0, 0);
    delay(50);
    Mouse.moveTo(0, halfHeight);
    //Mouse.set_buttons(1, 0, 0);
    delay(50);
    Mouse.moveTo(width, halfHeight);
    //Mouse.set_buttons(0, 0, 0);
    delay(50);
    Mouse.moveTo(0, 0);
    justReset = true;
    delay(50);
  }

  if (i <= (width - startX)) {
    int powered = pow(i,2);
    int yVal = powered * -1;
    Serial.println("x: " + i);
    Serial.println("y: " + yVal);
    //Mouse.moveTo(i, yVal);
    if (justReset) {
      //Mouse.set_buttons(1, 0, 0);
      justReset = false;
    }
    i++;
  } else {
    i = startX;
    Mouse.set_buttons(0, 0, 0);
    Mouse.moveTo(0, 0);
    delay(4000);
  }

  delay(50);
}
