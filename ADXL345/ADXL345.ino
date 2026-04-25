/*
 * Project name: ADXL345
 * Description: Example using ADXL345 acelerometer. The display shows x,y,z gravity force measure.
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 24.04.26
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
 *
 * Other Notes:
 *
 */

// #include "gpio.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "userADXL345.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GPIO_3    3

// GPIOInput button(ACTIVE_LOW_LEVEL);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //0x3C is display i2c address
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();    //Load the screen

}

void loop() {
    adxl_update();
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
    display.println("G MESURE FORCE");
    display.setTextSize(1);
    display.setCursor(0, 27);
    display.println("X Axis: " + String(xg_force));
    display.setCursor(0, 36);
    display.println("Y Axis: " + String(yg_force));  
    display.setCursor(0, 45);
    display.println("Z Axis: " + String(zg_force));  
    display.display();
    delayMicroseconds(100);
}