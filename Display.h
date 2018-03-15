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

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#ifndef USED_DIGITS
#define USED_DIGITS 4
#endif

#include <Arduino.h>

#include "Segment.h"
#include "Digit.h"

typedef bool num_segs_t[10][7];

class Display {

private:
  Segment *segments[7];
  Digit *digits[USED_DIGITS];
  DecimalPoint *dp;

public:
#ifdef DISABLE_DP
  Display(byte digit_pins[USED_DIGITS], byte segment_pins[7]) {
#else
  Display(byte digit_pins[USED_DIGITS], byte segment_pins[7], byte dp_pin) {
    dp = new DecimalPoint(dp_pin);
    dp->toggle(false);
#endif
    for (int i = 0; i < USED_DIGITS; i++) {
      digits[i] = new Digit(digit_pins[i]);
      digits[i]->toggle(false);
    }

    for (int i = 0; i < 7; i++) {
      segments[i] = new Segment(segment_pins[i]);
      segments[i]->toggle(false);
    }
  }

#ifdef DISABLE_DP
  void print(const char num[USED_DIGITS]);
#else
  void Display::print(const char num[USED_DIGITS+1]);
#endif
};

#endif // DISPLAY_H_INCLUDED
