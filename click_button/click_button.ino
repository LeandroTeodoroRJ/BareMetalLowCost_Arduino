/*
 * Project name: Click Button 
 * Description: How to use GPIO click button class (push-button modeling)
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 02.04.26
 * Dependences: 
 *   -- gpio.h v1.1 
 *   -- Adafruit SSD1306 v.2.5.14 by Adafruit
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano V3
 * Compile/Interpreter: Arduino IDE Ver 2.3.8
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links:
 *
 * Other Notes: 
 *    -- The input is defined by GPIO number, not Dx number.
 *
 */

#include "gpio.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GPIO_3    3

ClickButton button(ACTIVE_LOW_LEVEL); 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int value;

void screen_update(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
  display.println("COUNT");
  display.setTextSize(3);
  display.setCursor(0, 18);
  display.println(String(value));    
  display.display();
}

void setup() {
  value = 0;
  Serial.begin(115200);
  delay(10);
  button.setPin(GPIO_3);
  button.setDebounce(DEBOUNCE_ACTIVE);

  // 0x3C is default i2c adress in some cases MAY be different
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //0x3C is display i2c address
  display.clearDisplay();;
  display.setTextColor(WHITE);  
  display.display();    //Load the screen
  screen_update();
}

void loop() {
  button.button_scan(); 
  if (button.click_button_event()){
     value = value + 1;
     button.click_button_finish_event();
     screen_update();
  }
  else{
     delayMicroseconds(100);
  }
}
