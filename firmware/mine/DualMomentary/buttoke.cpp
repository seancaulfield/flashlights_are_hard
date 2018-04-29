/*
 * butttoke.cpp
 *
 * Wrapper around button library to encapsulate button pushing state machine,
 * outputing tokens to use to drive another state machine for behavior. Keeps
 * track of all the BS of long vs. short press.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 */

#include "buttoke.h"

ButtTokenizer::ButtTokenizer(
    int pin,
    bool pullup,
    bool invert,
    int debounce_ms,
    int double_tap_timeout,
    int min_long_press_ms,
    int long_press_interval_ms
) :
  myButt(pin, pullup, invert, debounce_ms),
  myState(BUTT_WAIT),
  pressStart(0),
  pushCounter(0),
  doubleTapTimeout(double_tap_timeout),
  minLongPress(min_long_press_ms),
  longPressInterval(long_press_interval_ms)
{
}
