/*
 * Description: Arduino Timer 1 driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/BareMetalLowCost_Arduino
 * Stable: Yes
 * Version: 1.0.1
 * Last Uptate: 01.08.26
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: Arduino Nano
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 *   -- All libraries that need access specials registers 
 *      must need include Arduino.h 
 *
 */

#ifndef TIMER1_H
#define TIMER1_H

#include <Arduino.h>

void configure_timer1_interrupt(void);

#endif	/* TIMER1_H */