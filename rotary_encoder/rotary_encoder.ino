/*
 * Project name: Rotary Encoder 
 * Description: How to use a rotary encoder with easy example
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 02.04.26
 * Dependences: 
 *   -- gpio.h v1.1 
 *   -- r_encoder v1.0
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
#include "r_encoder.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GPIO_3    3
#define GPIO_4    4
#define GPIO_5    5
#define GPIO_6    6

RotaryEncoder encoder(GPIO_4, GPIO_5, GPIO_6);
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
  encoder.cb_button.button_scan();

  value = encoder.pooling_scan();
  
  if (encoder.rotary_event()){
  //  Serial.println(value);
    screen_update();
    encoder.finish_event();
  }

  if (encoder.cb_button.click_button_event()){
    value = 0;
    encoder.reset();
    screen_update();
    encoder.cb_button.click_button_finish_event();
  }

  if (button.click_button_event()){    
    value = 150;
    encoder.set_rotary_value(150);
    screen_update();
    button.click_button_finish_event();
  }
  
}
