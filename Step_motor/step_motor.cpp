#include "Arduino.h"
#include "step_motor.h"
#include "gpio.h"

StepMotorDM556::StepMotorDM556(int pulse_pin, int direction_pin){
  this->pulse.setPin(pulse_pin);
  this->direction.setPin(direction_pin);
}

void StepMotorDM556::setEnable(int enable_pin){
  this->enable.setPin(enable_pin);
}

void StepMotorDM556::resetDelay(void){
  this->_delay_to_pulse = 0;
}

uint16_t StepMotorDM556::getDelay(void){
  return this->_delay_to_pulse;
}

void StepMotorDM556::incrementDelay(void){
  this->_delay_to_pulse++;
}

void StepMotorDM556::step(void){
  if(this->_direction == 0){
    this->direction.deactivate();
  }else{
    this->direction.activate();
  }
  this->_pulse = !this->_pulse;
  if(this->_pulse == 1){
    this->pulse.activate();
  }else{
    this->pulse.deactivate();
  }
}

void StepMotorDM556::setDirection(bool dir){
  this->_direction = dir;
}
