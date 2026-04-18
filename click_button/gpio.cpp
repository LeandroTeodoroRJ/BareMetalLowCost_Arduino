#include "Arduino.h"
#include "gpio.h"

void button_event();

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


ClickButton::ClickButton(int level):GPIOInput(level) { }

void ClickButton::button_scan(int (*event)()){
  if (this->isActive()){
    if (this->button_release == TRUE){
      if (this->executed == FALSE){
        this->activated = TRUE;   //Put false after the event
        this->button_release = FALSE;
        this->executed = TRUE;
      }
    }  
    else{
      this->activated = FALSE; 
      this->button_release = FALSE; 
    }
  }
  else{
    this->activated = FALSE; 
    this->button_release = TRUE;  
  }
   if (this->click_button_event()){
    button_event();
    this->click_button_finish_event();
  }
}

int ClickButton::click_button_event(){
  if (this->activated == TRUE){
    return TRUE;    
  }
  else{
    return FALSE;
  } 
}

void ClickButton::click_button_finish_event(){
  this->executed = FALSE;  
}
