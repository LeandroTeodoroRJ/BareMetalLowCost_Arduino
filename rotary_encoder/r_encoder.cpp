#include "Arduino.h"
#include "r_encoder.h"
#include "gpio.h"

RotaryEncoder::RotaryEncoder(uint8_t pin_button, uint8_t pin_clk, uint8_t pin_dt){
  cb_button.setDebounce(DEBOUNCE_NOT_ACTIVE);
  cb_clk.setDebounce(DEBOUNCE_NOT_ACTIVE);
  input_dt.setDebounce(DEBOUNCE_NOT_ACTIVE);
  cb_button.setPin(pin_button);
  cb_clk.setPin(pin_clk);
  input_dt.setPin(pin_dt); 
  _atual_value = 0; 
}

int RotaryEncoder::pooling_scan(){
  cb_clk.button_scan();
  if (cb_clk.click_button_event()){
      if (input_dt.isActive()){
        _atual_value = _atual_value - 1;
      }
      else{
        _atual_value = _atual_value + 1;
      }
      _activated = TRUE;
      cb_clk.click_button_finish_event();
    }
  return _atual_value;
}

void RotaryEncoder::finish_event(){
  _activated = FALSE; 
}

bool RotaryEncoder::rotary_event(){
  if (_activated == TRUE){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void RotaryEncoder::reset(){
  _atual_value = 0;
}

void RotaryEncoder::set_rotary_value(int value){
  _atual_value = value;
}