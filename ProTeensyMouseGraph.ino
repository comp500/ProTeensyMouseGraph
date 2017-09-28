int startX = -10; // maths units
int startY = 10; // maths units
float i = startX; // maths units
int height = 20; // maths units
int width = 20; // maths units
boolean justReset = false;

void setup() {
  Mouse.screenSize(40, 40);
  Serial.begin(9600);
}

void loop() {
  if (i == startX) {
    int halfHeight = height / 2;
    int halfWidth = width / 2;
    Mouse.move(halfWidth, 0);
    Mouse.set_buttons(1, 0, 0);
    Mouse.move(halfWidth, height);
    Mouse.set_buttons(0, 0, 0);
    Mouse.move(0, halfHeight);
    Mouse.set_buttons(1, 0, 0);
    Mouse.move(width, halfHeight);
    Mouse.set_buttons(0, 0, 0);
    Mouse.move(0, 0);
    justReset = true;
  }

  if (i <= (width - startX)) {
    Mouse.move(i, pow(i/2,2) * -1);
    if (justReset) {
      Mouse.set_buttons(1, 0, 0);
      justReset = false;
    }
    i++;
  } else {
    i = startX;
    Mouse.set_buttons(0, 0, 0);
    Mouse.move(0, 0);
    delay(4000);
  }

  delay(50);
}
