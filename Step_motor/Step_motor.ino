/*
 * Project name: Step Motor 
 * Description: How to use step motor library
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 31.07.26
 * Dependences: 
 *   -- gpio.h v2.0.0 
 *   -- step_motor.h v1.0.0
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


#include "gpio.h"
#include "step_motor.h"

#define GPIO_10   10
#define GPIO_11   11
#define DELAY_TIME_MS 10

StepMotorDM556 motor(GPIO_10, GPIO_11);

void configure_1ms_timer1_interrupt(){
  // Clear Timer 1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // Clear timer counter

  // Set the compare match value for a 1 ms interval
  // Formula: OCR1A = (16MHz / (Prescaler * Desired_Frequency)) - 1
  // Desired frequency for 1ms = 1000 Hz (1 kHz)
  // OCR1A = (16000000 / (64 * 1000)) - 1 = 249
  // OCR1A = 249;
  OCR1A = 24;   //To 100us interruption time

  // Enable CTC (Clear Timer on Compare Match) mode via WGM12 bit
  TCCR1B |= (1 << WGM12);

  // Set Prescaler to 64 (Turn on CS11 and CS10 bits)
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Enable Timer 1 Compare Match A interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void setup() {
  Serial.begin(115200);   
  noInterrupts(); // Disable global interrupts during configuration
  configure_1ms_timer1_interrupt();  
  motor.setDirection(ANTICLOCKWISE);
  interrupts();  // Re-enable global interrupts  
  motor.setTarget(-400);
}

// Timer 1 Interrupt Service Routine (executed exactly every 1 ms)
ISR(TIMER1_COMPA_vect) {  
  if (DELAY_TIME_MS >= motor.getDelay()){
    motor.incrementDelay(); //Wait delay time for motor step velocity
  }else{
    motor.resetDelay();
    motor.step();
  }
}

void loop() {
//  Serial.println("OK");
  delay(20000); 
//  motor.resetCounter();
}

