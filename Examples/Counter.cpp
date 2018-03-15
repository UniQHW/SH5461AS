/*

 * Copyright (c) 2018 Patrick Pedersen <ctx.xda@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

 */


#include <Arduino.h>
#include <string.h>

#include "Segment.h"
#include "Digit.h"
#include "Display.h"

byte digit_pins[3] {A1, A2, A3};
byte seg_pins[7] {A5, 12, 11, 0, A4, A0, 10};

Display *d;

char buff[5];

unsigned long t_stamp;

void setup() {
  for (int i = 0; i <= A5; i++) {
    pinMode(i, OUTPUT);
  }

  d = new Display(digit_pins, seg_pins);
}

void loop() {
  static int i = 0;
  t_stamp = millis();

  sprintf(buff, "%d", i);

  while(millis() - t_stamp < 1000) {
    d->print(buff);
  }

  if (i == 999) {
    i = 0;
  } else {
    i++;
  }
}
