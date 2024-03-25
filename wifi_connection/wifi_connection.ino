/*
 * Project name: Wifi connection
 * Description: How to connect on wifi network
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 15.03.24
 * Dependences: ESP8266WiFi
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No
 *
 */

#include <ESP8266WiFi.h>

const char* ssid = "network_ssid_name";  //network_ssid_name
const char* password = "password";

void setup() {
  //Serial port settings
  Serial.begin(115200);
  delay(10);

  //Wifi inicialization
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected on Wifi");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:

}
