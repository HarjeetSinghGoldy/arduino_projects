/*
 * Beating heart on 8x8 LED using Arduino UNO
 *
 * Copyright (C) 2011, 2015 R.W. van 't Veer
 */

#include <FrequencyTimer2.h>

byte row[8] = { 2, 7, 19, 5, 13, 18, 12, 16 };
byte col[8] = { 6, 11, 10, 3, 17, 4, 8, 9 };

byte heart[8][8] = {{ 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 1, 1, 0, 1, 1, 0, 0 },
                    { 1, 1, 1, 1, 1, 1, 1, 0 },
                    { 1, 1, 1, 1, 1, 1, 1, 0 },
                    { 0, 1, 1, 1, 1, 1, 0, 0 },
                    { 0, 0, 1, 1, 1, 0, 0, 0 },
                    { 0, 0, 0, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0 }};

boolean visible = 0;

void display() {
  for (int y = 0; y < 8; y++) {
    digitalWrite(row[y], HIGH);
    for (int x = 0; x < 8; x++) {
      int thisPixel = (heart[y][x] && visible) ? LOW : HIGH;
      digitalWrite(col[x], thisPixel);
      if (thisPixel == LOW) {
        digitalWrite(col[x], HIGH);
      }
    }
    digitalWrite(row[y], LOW);
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(col[i], OUTPUT);
    pinMode(row[i], OUTPUT);
    digitalWrite(col[i], HIGH);
  }

  FrequencyTimer2::disable();
  FrequencyTimer2::setPeriod(2000);
  FrequencyTimer2::setOnOverflow(display);
}

void loop() {
  visible = 1;
  delay(200);
  visible = 0;
  delay(300);
  visible = 1;
  delay(200);
  visible = 0;
  delay(750);
}

