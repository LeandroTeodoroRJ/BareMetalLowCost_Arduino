/*
 * Project name: IDE Serial Port
 * Description: Undertanding how the IDE Serial port works
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: jan/26
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: Arduino Nano v3
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: https://docs.arduino.cc/language-reference/en/functions/communication/serial/
 * Other Notes: No.
 *
 */

#define received_new_data 1

String text;
int insert_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
//  Serial.print("Hello Serial Monitor \n");
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available() == received_new_data)
  {
    text = Serial.readString();
    Serial.print(text);
    insert_value = text.toInt();    //Or if applicable text.toFloat()
    if (insert_value >= 100){
      Serial.println("High Value");
    }else{
      Serial.println("Low Value");
    }
  }
}
