/*
 * Project name: Wifi connection
 * Description: How to connect on wifi network
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 08.06.24
 * Dependences: genericWiFi
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No
 *
 */

#include "genericWiFi.h"

#define TIME_10_MS    10
#define RATE_115KBPS  115200

const char* ssid = SSID_NAME;     //wifi ssid name --string
const char* password = PASSWORD;  //wifi password --string

void setup() { 
  serialMonitorStart();
  WiFi.begin(ssid, password);
  WifiWatingConnect();  
  wifiConnectedStatus();
}

void serialMonitorStart(){ 
    Serial.begin(RATE_115KBPS);
    delay(TIME_10_MS);
}

void loop() {
  // put your main code here, main loop... 
}




