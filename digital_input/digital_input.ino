/*
 * Project name: Digital Input
 * Description: Read a GPIO pin
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 18.03.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: The input is defined by GPIO number, not Dx number.
 *
 */

#define GPIO_16   16
#define BUTTON    GPIO_16

int value = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(BUTTON, INPUT);
}

void loop() {
  
  // Read a input pin
  value = digitalRead(BUTTON);
 
  // Send te input state
  Serial.println(value);                              
  delay(1000);             
}
