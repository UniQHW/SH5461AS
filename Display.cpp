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

#include "Display.h"

num_segs_t num_segs
{
  {true, true, true, true, true, true, false},     // 0
  {false, true, true, false, false, false, false}, // 1
  {true, true, false, true, true, false, true},    // 2
  {true, true, true, true, false, false, true},    // 3
  {false, true, true, false, false, true, true},   // 4
  {true, false, true, true, false, true, true},    // 5
  {true, false, true, true, true, true, true},     // 6
  {true, true, true, false, false, false, false},  // 7
  {true, true, true, true, true, true, true},      // 8
  {true, true, true, true, false, true, true}      // 9
};

void Display::print(const char num[3]) {
  for (int i = 0; i < 3; i++) {
    if(num[i] == '\0') {
      continue;
    }

    for (int j = 0; j < 7; j++) {
      segments[j]->toggle(num_segs[num[i] - 0x30][j]);
    }

    /* Add 1ms offset for previous digit to clear, in order to prevent flickering from upcoming digit */
    delay(1);
    digits[i]->toggle(true);

    /* Provide digit sufficient time to display */
    delay(1);
    digits[i]->toggle(false);
  }
}
