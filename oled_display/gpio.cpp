#include "Arduino.h"
#include "gpio.h"

GPIOPin::GPIOPin(int level){
	_is_active = level;
}

void GPIOPin::setMode(uint8_t direction){
	_mode = direction;
	pinMode(_pin, _mode);
}

GPIOInput::GPIOInput(int level):GPIOPin(level) { }

void GPIOInput::setPin(uint8_t pin){
  _pin = pin;
  this->setMode(INPUT);
}

int GPIOInput::isActive(){
  if ( _isBebounceActive == TRUE){
    delay(DEBOUNCE_TIME_MS);
  }
	int read_pin = digitalRead(_pin);
	if (read_pin == _is_active){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void GPIOInput::setDebounce(bool isBebounceActive){
  _isBebounceActive = isBebounceActive;
}

GPIOOutput::GPIOOutput(int level):GPIOPin(level) { }

void GPIOOutput::setPin(uint8_t pin){
  _pin = pin;
  this->setMode(OUTPUT);
}

void GPIOOutput::activate(){
  if (_is_active == HIGH_LEVEL){
    digitalWrite(_pin, HIGH);
  }
  else{
    digitalWrite(_pin, LOW);
  }
}

void GPIOOutput::deactivate(){
  if (_is_active == HIGH_LEVEL){
    digitalWrite(_pin, LOW);
  }
  else{
    digitalWrite(_pin, HIGH);
  }
}

