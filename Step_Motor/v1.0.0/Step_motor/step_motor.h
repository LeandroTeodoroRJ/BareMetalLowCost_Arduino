/*
 * Description: Step Moptor library using DM556 driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 01.08.26
 * Dependences:
 *  -- gpio.h v2.0.1
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: Arduino Nano
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 *   -- This library uses Timer 1 interrupt to execute motor steps motion.
 *
 */

 #ifndef STEP_MOTOR_H
 #define STEP_MOTOR_H

 #include "gpio.h"

 #define CLOCKWISE 1
 #define ANTICLOCKWISE 0

 class StepMotorDM556{
	private:        
   protected:   
    int16_t _counter_target = 0;
    int16_t _actual_counter = 0;
    uint16_t _delay_to_pulse = 0;
    bool _pulse = 0;
    bool _direction = 0;
    GPIOOutput pulse {ACTIVE_HIGH_LEVEL};
    GPIOOutput direction {ACTIVE_HIGH_LEVEL};
    GPIOOutput enable {ACTIVE_HIGH_LEVEL};
	 public:
    StepMotorDM556(int pulse_pin, int direction_pin);
    void setEnable(int enable_pin);
    void resetDelay(void);  
    uint16_t getDelay(void);
    void incrementDelay(void); 
    void step(void); 
    void setDirection(bool dir);
    void setTarget(int16_t target);
    void resetCounter(void);
 };
  
 #endif	/* STEP_MOTOR_H */