/*
 * Project name: Tiny RTC
 * Description: How to use the tiny RTC module with graphical display
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 02.04.26
 * Dependences:  
 *   -- Adafruit SSD1306 v.2.5.14 by Adafruit
 *   -- DS1307.h v1.0.0
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

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DS1307.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GPIO_3    3
#define GPIO_4    4
#define GPIO_5    5
#define GPIO_6    6

String full_date;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  

void print_date(){  
  Serial.print(day);
  Serial.print("/");
  Serial.print(mounth);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  full_date = String(day) + "/" + String(mounth) + "/" + String(year) + "\n" + String(hour) + ":" + String(minutes) + ":" + String(seconds);
}

void screen_update(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);         // setCursor(x, y) x:col y:rol - mesure pixel
  display.println("DATE");
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.println(full_date);    
  display.display();
}

void setup(){
  Wire.begin();
  Serial.begin(115200);
  setDateTime(4, 17, 26, 6, 16, 34, 1);      


  // 0x3C is default i2c adress in some cases MAY be different
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   //0x3C is display i2c address
  display.clearDisplay();;
  display.setTextColor(WHITE);  
  display.display();    //Load the screen
  screen_update();
}

void loop(){
  get_date();
  print_date();
  screen_update();
  delay(1000);
}

