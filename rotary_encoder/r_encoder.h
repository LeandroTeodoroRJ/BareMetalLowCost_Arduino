/*
 * Description: Rotary Encoder Library
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 10.04.26
 * Dependences:
 *     -- gpio.h v1.1
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 *    -- Don't forget the pull-up resistor on SW pin.
 *
 */


#ifndef R_ENCODER_H
#define R_ENCODER_H

#include "gpio.h"

class RotaryEncoder{
  private:  
    bool _activated = FALSE;
    ClickButton cb_clk {ACTIVE_HIGH_LEVEL};
    GPIOInput input_dt {ACTIVE_LOW_LEVEL};   //Clockwise
    int _atual_value;      
  protected:
  public:
    ClickButton cb_button {ACTIVE_LOW_LEVEL}; 
    RotaryEncoder(uint8_t pin_button, uint8_t pin_clk, uint8_t pin_dt);
    int pooling_scan(); 
    void finish_event();
    bool rotary_event(); 
    void reset();
    void set_rotary_value(int value);
};

#endif	/* R_ENCODER_H */