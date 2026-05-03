/*
 * Project name: Serial Port
 * Description: How to use the "external" serial port
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 26.03.26
 * Dependences: gpio.h v1.0
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano V3
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links:
 *    MiniCore Arduino IDE link to install : https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
 *    MiniCore GitHub Manual: https://github.com/mcudude/minicore?tab=readme-ov-file#supported-microcontrollers
 *    Burn BootLoader : https://www.youtube.com/watch?v=LvKr8gG_WNg
 *    How to Porgram ATmega328PB (PT-BR) : https://www.youtube.com/shorts/q162V5aGD1Q
 *    miniCore e Optiboot : https://www.youtube.com/watch?v=IEePUliK3K4
 *    Programer FIX error: https://andreasrohner.at/posts/Electronics/How-to-fix-device-permissions-for-the-USBasp-programmer/
 * Other Notes: 
 *    -- The input is defined by GPIO number, not Dx number.
 *
 */

#include "gpio.h"

#define GPIO_3    3

GPIOInput button(ACTIVE_LOW_LEVEL); 
 
void setup() {
  Serial1.begin(115200);
  delay(10);
  button.setPin(GPIO_3);
  button.setDebounce(DEBOUNCE_NOT_ACTIVE);
}

void loop() {
  if (button.isActive()){
    delayMicroseconds(500);
  }
  else{
    delayMicroseconds(100);
  }
// Serial.println(button.isActive());
}
