/*
 * Project name: GPIO pins
 * Description: How to use a GPIO
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 11.06.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: 
 *    -- The input is defined by GPIO number, not Dx number.
 *    -- isActive method (GPIOOutput class) not implemented
 *
 */

#include "gpio.h"

#define GPIO_16   16
#define GPIO_2    2

GPIOInput button(ACTIVE_LOW_LEVEL);   
GPIOOutput led(ACTIVE_LOW_LEVEL);     

void setup() {
  Serial.begin(115200);
  delay(10);
  button.setPin(GPIO_16);
  button.setDebounce(DEBOUNCE_NOT_ACTIVE);
  led.setPin(GPIO_2); 
}

void loop() {
  if (button.isActive()){
    led.activate();
  }
  else{
    led.deactivate();
  }
  Serial.println(button.isActive());
}
