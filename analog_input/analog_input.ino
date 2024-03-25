/*
 * Project name: Analog Input
 * Description: Readaing the analog input pin
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 24.03.24
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No.
 *
 */

#define ANALOG_PIN  A0

int analog_value = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
}

void loop() {
  analog_value = analogRead(ANALOG_PIN);
  Serial.print("Analog Value: ");
  Serial.println(analog_value);
  delay(500);
}


