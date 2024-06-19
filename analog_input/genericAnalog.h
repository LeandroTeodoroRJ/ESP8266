/*
 * Description: This class implement to read a analog input pin
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 10.06.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No.
 *
 */


#ifndef GENERIANALOG_H
#define GENERIANALOG_H

#include "Arduino.h"

#define MAX_VALUE_ERROR 1

class AnalogInput{
private:
  uint8_t _analog_pin;  
  int _max_value;
public:
  AnalogInput(uint8_t pin);  
  int getValue();
  void setMaxValue(int value);    
};

#endif /* GENERIANALOG_H */