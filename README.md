# SH5461AS 4 Digit Segment Display Library

Just another library to communicate with the SHA5461AS 4 Digit Segment Display.

This library has been written in order to help a pupil of mine with his Arduino project.

![gif]()

## Installation

Download the repository as a zip
![Downloading the repo](img/.png)

After obtaining a local copy of the library, import the library in the [Arduino IDE](https://create.arduino.cc/):
![Importing the library](img/Import.png)

## Importing/Including

Add the following to the top of your source file in order to include this library:
```cpp
#include "Segment.h"
#include "Digit.h"
#include "Display.h"
```

## Example

The following example prints `1.234` to the display
```cpp
#include <Arduino.h>

/* Include this library */
#include "Segment.h"
#include "Digit.h"
#include "Display.h"

const byte digit_pins[3] {A1, A2, A3}; // From com1 - com4
const byte segment_pins[7] {A5, 12, 11, 0, A4, A0, 10}; // From a - g (abc...g)
const byte dp_pin = 1;

Display *d

void setup() {
  for (int i = 0; i <= A5; i++) {
    pinMode(i, OUTPUT);
  }

  d = new Display(digit_pins, segment_pins, 1);
}

void loop() {
  d->print("1.234") // Must be looped!
}
```

Setup used for example:
![fritzing]()

Result:

![result](img/result.png)

## Flags

The following preprocessor directives may be used to optimize the library:

|Preprocessor |Description          |
|-------------|---------------------|
|`#DISABLE_DP`|Disables support for decimal points, minimally increasing frame rate|
|`#USED_DIGITS N`|Limits display to only use first N digits|


Preprocessors must be set **BEFORE** the library is included:

```cpp
#define DISABLE_DP
#define USED_DIGITS 3

#include "Segment.h"
#include "Digit.h"
#include "Display.h"
```

Turning off specific digits disregarding the position, can be done using the `\0` character (See `print` in [`class Dispaly`)](#class-display))

## Library Overview

The library provides a total of three classes:

|Class|Defined In|Description|
|-----|----------|-----------|
|Display|[Display.h](https://github.com/UniQHW/SH5461AS/blob/master/Digit.h#L30)|Display controller class|  
|Digit|[Digit.h](Digit.h)|Hardware abstraction for COM pins|
|Segment|[Segment.h](Segment.h)|Hardware abstraction for segments|

The Display class acts as a display controller and should be sufficient for most applications. It comes with a `print` function that displays the provided number string on the display. See [`class Display`](#class-display) for more.

### `class Display`
A display controller class

#### Constructor
The constructor is provided with the necessary pin information in order to successfully communicate with the display.

```cpp
#ifdef DISABLE_DP
  Display(byte digit_pins[USED_DIGITS], byte segment_pins[7])
#else
  Display(byte digit_pins[USED_DIGITS], byte segment_pins[7], byte dp_pin)
#endif
```

|Parameter|Description|Example|
|---------|-----------|-------|
|`byte digit_pins[USED_DIGITS]`|Array of digit pins `COM1 - COM4`|`byte digit_pins[4] {A1, A2, A3, A4};`|
|`byte segment_pins[7]`|Array of segment pins `a - g (abc..g)`|`byte segment_pins[7] {A5, 12, 11, 0, A4, A0, 10};`|
|`byte dp_pin`|Pin to control Decimal Point. Leave out if `#DISABLE_DP` has been defined|`1`|

![datasheet](http://mklec.com/image/data/displays/7-segment-4-digit-display-common-anode-12-pin--pinout.png)

#### Members

|Member|Access|Description|
|------|------|-----------|
|`bool state`|Private|A private state buffer for `toggle()`|
|`Digit *digits[USED_DIGITS]`|Public|Stores [digit objects](#digit) to activate/disable COMs|
|`Segment *segments[7]`|Public|Stores [segment objects](#segment) from `a - g (abc...g)` to activate and disable segments|
|`DecimalPoint *dp`|Public|Stores dp object (alias to [segment objects](#segment)) to activate/disable dp|

#### Member Functions

##### `void print(const char[])`
> Access: Public

Prints a string of numbers onto display. The string may only include characters `\0`, `0-9` and `.` (unless `#DISABLE_DP` has been defined). **The print function requires to be constantly refreshed!**

If `\0` has been provided, no number is displayed (Ex: `print("1\0\01")` will display 1 on the first and last digit only).

Because speed is crucial, this function provides no error-checking. As a result, if too many, or invalid characters have been specified, the display will return unpredictable/wrong results.

###### Example
```cpp
void loop() {
  d->print("1.234")
}
```

![result](img/result.png)

##### `void toggle()`
> Access: Public

Toggles **all** digits on or off, depending on it's previous state.

|Display prior toggle|Display after toggle|
|--------------------|--------------------|
|OFF|ON|
|ON|OFF|

##### `void toggle(bool arg_state)`
> Access: Public

Sets **all** digits to the provided state.

|State|Display after toggle|
|-----|--------------------|
|true|ON|
|false|OFF|

##### `void fill(bool all = true)`
> Access: Public

Turns all segments and decimal points to '**ON**' (unless `#DISABLE_DP` has been defined). If `bool all` has been set to `false`, only digits that are '**ON**' will be filled.

![filled]()

##### `void empty()`
> Access: Public

Turns all segments and decimal points to '**OFF**'.

### `class Digit`
A hardware abstraction for COM pins

The constructor is provided with the necessary pin information in order to successfully communicate with the display.

```cpp
Segment(byte pin);
```

|Parameter|Description|Example|
|---------|-----------|-------|
|`byte pin`|COM pin|`A1`|

#### Members

|Member|Access|Description|
|------|------|-----------|
|`byte pin`|Private|COM pin|
|`bool state`|Private|A private state buffer for `toggle()`|
