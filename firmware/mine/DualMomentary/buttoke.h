/*
 * butttoke.h
 *
 * Wrapper around button library to encapsulate button pushing state machine,
 * outputing tokens to use to drive another state machine for behavior. Keeps
 * track of all the BS of long vs. short press.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 */

#ifndef _BUTTOKE_H
#define _BUTTOKE_H

#include <Arduino.h>
#include <Button.h>

typedef enum {
  BUTT_WAIT,
  BUTT_PRESSED,
  BUTT_RELEASED,
} butt_state_t;

class ButtTokenizer
{
  public:
    ButtTokenizer(int pin,          // Arduino/Wiring pin number
        bool pullup,                // Activate pullups?
        bool invert,                // If true, HIGH=false, else HIGH=true
        int debounce_ms,            // Debounce time
        int double_tap_timeout_ms,  // How long to wait for another button push
                                    // after the button is released?
        int min_long_press_ms,      // How long to wait after being pushed
                                    // before reporting back a button-held-down
                                    // event?
        int long_press_interval_ms  // How often to return button-held-down
                                    // events after the initial timeout
      );
    
  protected:
    Button myButt;
    butt_state_t myState;
    uint32_t pressStart;
    uint8_t pushCounter;
    int doubleTapTimeout;
    int minLongPress;
    int longPressInterval;
};

#endif //_BUTTOKE_H
