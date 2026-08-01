/*
 * Project name: Step Motor 
 * Description: How to use step motor library
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 31.07.26
 * Dependences: 

 *   -- step_motor.h v1.0.0
 *   -- timer1.h v1.0.0
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

#include "step_motor.h"
#include "timer1.h"

#define GPIO_10   10
#define GPIO_11   11
#define DELAY_TIME_MS 10

StepMotorDM556 motor(GPIO_10, GPIO_11);

void setup() {
  Serial.begin(115200);   
  noInterrupts(); // Disable global interrupts during configuration
  configure_1ms_timer1_interrupt();  
  motor.setDirection(ANTICLOCKWISE);
  interrupts();  // Re-enable global interrupts  
  motor.setTarget(-400);
}

// Timer 1 Interrupt Service Routine (executed exactly every 100 us)
ISR(TIMER1_COMPA_vect) {  
  if (DELAY_TIME_MS >= motor.getDelay()){
    motor.incrementDelay(); //Wait delay time for motor step velocity
  }else{
    motor.resetDelay();
    motor.step();
  }
}

void loop() {
  delay(5000); 
//  motor.resetCounter();   // Reset to motor move again
}

