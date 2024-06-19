/*
 * Project name: Analog Input
 * Description: Read the analog input pin from potentiometer
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

#include "genericAnalog.h"

#define TIME_500_MS   500
#define RATE_115KBPS  115200
#define TIME_10_MS 10

AnalogInput potentiometer(A0);
int analog_value = 0;

void setup() {
  Serial.begin(RATE_115KBPS);
  delay(TIME_10_MS);
}

void loop() {
  potentiometer.setMaxValue(800);
  analog_value = potentiometer.getValue();
  showMessageValue(analog_value);
  delay(TIME_500_MS);
}

void showMessageValue(int value){
  Serial.print("Analog Value: ");
  Serial.println(value);
  Serial.println(" ");
}

