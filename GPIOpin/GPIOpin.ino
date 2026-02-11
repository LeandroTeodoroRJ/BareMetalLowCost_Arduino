/*
 * Project name: GPIO pins
 * Description: How to use a GPIO
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 30.01.26
 * Dependences: gpio.h v1.0
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano V3
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: 
 *    -- The input is defined by GPIO number, not Dx number.
 *    -- isActive method (GPIOOutput class) not implemented
 *
 */

#include "gpio.h"

#define GPIO_3    3
#define GPIO_2    2

GPIOInput button(ACTIVE_LOW_LEVEL);   
GPIOOutput led(ACTIVE_HIGH_LEVEL);     

void setup() {
  Serial.begin(115200);
  delay(10);
  button.setPin(GPIO_3);
  button.setDebounce(DEBOUNCE_NOT_ACTIVE);
  led.setPin(GPIO_2); 
}

void loop() {
  if (button.isActive()){
    led.activate();       //Remember... LED is active in high level
  }
  else{
    led.deactivate();
  }
// Serial.println(button.isActive());
}
