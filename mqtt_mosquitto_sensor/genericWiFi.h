/*
 * Description: General Wifi functions
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 08.06.24
 * Dependences: Arduino, ESP8266WiFi, security
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

#ifndef GENERICWIFI_H
#define GENERICWIFI_H

#include "Arduino.h"
#include "security.h"

#ifdef ESP8266
  #include <ESP8266WiFi.h>     /* WiFi library for ESP8266 */
#else
  #include <WiFi.h>            /* WiFi library for ESP32 */
#endif

#define TIME_500_MS   500

bool wifiNotConnected();
void wifiConnectedStatus();
void WifiWatingConnect();

#endif /* GENERICWIFI_H */