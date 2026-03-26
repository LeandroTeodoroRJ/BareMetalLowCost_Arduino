/*
 * Project name: Oled I2C Display
 * Description: How to use the Oled I2C Display
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 26.03.26
 * Dependences: 
 *   -- gpio.h v1.0
 *   -- Adafruit SSD1306 v.2.5.14 by Adafruit
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano V3
 * Compile/Interpreter: Arduino IDE Ver 2.3.8
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links:
 *   Oled Examples : https://github.com/mcdominik/source/tree/main/arduino/oled_tutorial
 *   Adafruit GFX Library : https://github.com/adafruit/Adafruit-GFX-Library
 *   Guia Completo do Display OLED Como programar : https://blog.eletrogate.com/guia-completo-do-display-oled-parte-2-como-programar-3/
 *   Arduino with OLED Display : https://www.youtube.com/watch?v=___p9JYbTc0
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

GPIOInput button(ACTIVE_LOW_LEVEL); 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensor_number;
float sensor_value;
String info;
 
void setup() {
  Serial.begin(115200);
  delay(10);
  button.setPin(GPIO_3);
  button.setDebounce(DEBOUNCE_NOT_ACTIVE);

  // 0x3C is default i2c adress in some cases MAY be different
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //0x3C is display i2c address
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
  display.println("OLED Disp.");
  display.setTextSize(1);
  display.setCursor(0, 18);
  display.println("Example how to use \nthis display");
  display.display();    //Load the screen

}

void loop() {
  if (button.isActive()){
    delayMicroseconds(100);
    sensor_number = 5;
    sensor_value = 3.179;
    info = "Number:" + String(sensor_number) + " Value:" + String(sensor_value);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
    display.println("This a second title \nstyle screen");
    display.setTextSize(1);
    display.setCursor(0, 18);
    display.println("Second screen with \ninformations.");
    display.setCursor(0, 36);
    display.println("Sensor Information:");  
    display.setCursor(0, 45);
    display.println(info);  
    display.display();
  }
  else{
    delayMicroseconds(100);
  }

}
