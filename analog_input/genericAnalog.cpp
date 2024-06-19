#include "Arduino.h"
#include "genericAnalog.h"

AnalogInput::AnalogInput(uint8_t pin){
      _analog_pin = pin;     
  }

int AnalogInput::getValue(){
  int value = analogRead(_analog_pin);
  
    try{
      if (value > _max_value){
        throw(MAX_VALUE_ERROR);        
      }     
    }
    catch(int code){
      Serial.print("This value is excessefull. ");
    }  

    return value;
  }

void AnalogInput::setMaxValue(int value){  
  _max_value = value;
}