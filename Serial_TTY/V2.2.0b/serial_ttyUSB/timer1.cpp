#include "timer1.h"

void configure_timer1_interrupt(){
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
  
  TCCR1B |= (1 << WGM12);   // Enable CTC (Clear Timer on Compare Match) mode via WGM12 bit  
  TCCR1B |= (1 << CS11) | (1 << CS10);  // Set Prescaler to 64 (Turn on CS11 and CS10 bits)  
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer 1 Compare Match A interrupt
}