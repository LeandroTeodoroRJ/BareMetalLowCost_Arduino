/*
 * Project name: Timer 1
 * Description: How to use timer 1 interrupt on compare mode
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 31.07.26
 * Dependences: No 
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

// Variables modified inside an interrupt must be declared as 'volatile'
volatile unsigned long millisecondCounter = 0;

void configure_1ms_timer1_interrupt(){
  // Clear Timer 1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // Clear timer counter

  // Set the compare match value for a 1 ms interval
  // Formula: OCR1A = (16MHz / (Prescaler * Desired_Frequency)) - 1
  // Desired frequency for 1ms = 1000 Hz (1 kHz)
  // OCR1A = (16000000 / (64 * 1000)) - 1 = 249
  OCR1A = 249;

  // Enable CTC (Clear Timer on Compare Match) mode via WGM12 bit
  TCCR1B |= (1 << WGM12);

  // Set Prescaler to 64 (Turn on CS11 and CS10 bits)
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Enable Timer 1 Compare Match A interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void setup() {
  Serial.begin(115200);  

  // Configure pin 13 (built-in LED) as an output for visual testing
  pinMode(13, OUTPUT);  
  
  noInterrupts(); // Disable global interrupts during configuration
  configure_1ms_timer1_interrupt();  
  interrupts();  // Re-enable global interrupts
}

// Timer 1 Interrupt Service Routine (executed exactly every 1 ms)
ISR(TIMER1_COMPA_vect) {
  millisecondCounter++;
  
  // Toggle the LED every 500 ms (half a second) using our own counter
  if (millisecondCounter % 500 == 0) {
    digitalWrite(13, !digitalRead(13));
  }
}

void loop() {
  // The main loop remains 100% free for other tasks.
  // Print our counter value every 1 second to the serial monitor.
  Serial.print("Timer 1 Time: ");
  Serial.print(millisecondCounter);
  Serial.println(" ms");
  delay(1000); 
}

