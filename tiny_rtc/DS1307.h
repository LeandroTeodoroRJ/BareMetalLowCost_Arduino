/*
 * Description: Library to use DS1307 Real Time Clock
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 17.04.26
 * Dependences: 
 *   -- Wire.h
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: Arduino Nyear
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 *
 */

#define DS1307_ADDRESS 0x68
byte zero = 0x00;

int seconds;
int minutes;
int hour;
int weekday;
int day;
int mounth;
int year;

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}

void setDateTime(byte mounth, byte day, byte year, byte weekday, byte hour, byte minutes, byte seconds){ 
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); 
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(mounth));
  Wire.write(decToBcd(year));
  Wire.write(zero); 
  Wire.endTransmission();
}

void get_date(){
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  seconds = bcdToDec(Wire.read());
  minutes = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0b111111);    //24 hours format
  weekday = bcdToDec(Wire.read());             //0-6 -> Sunday - Saturday
  day = bcdToDec(Wire.read());
  mounth = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

