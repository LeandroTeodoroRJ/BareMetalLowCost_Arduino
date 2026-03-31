/*
 * Project name: Ultrassonic Sensor HC-SR04 and Oled Display
 * Description: How to use the ultrassonic sensor and oled display to mesure a distance
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.
 * Last Uptate: 26.03.26
 * Dependences: 
 *   -- Ultrasonic Created by ITead studio. Alex, Apr 20, 2010.
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

#include "Ultrasonic.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 

#define GPIO_4  4
#define GPIO_5  5
#define GPIO_3    3
#define pin_trigger GPIO_4
#define pin_echo GPIO_5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

Ultrasonic ultrasonic(pin_trigger, pin_echo);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //0x3C is display i2c address
  display.setTextColor(WHITE);
}
 
void loop()
{ 
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN); 
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
  display.println("Program Example \mDistance Measure");
  display.setTextSize(1);
  display.setCursor(0, 27);
  display.println("CM Distance: " + String(cmMsec));
  display.setCursor(0, 36);
  display.println("POL Distance: " + String(inMsec));  
  display.display();
  delay(1000);
}