#include "Arduino.h"
#include "genericWiFi.h"

void WifiWatingConnect(){
  while (wifiNotConnected()){
      delay(TIME_500_MS);
      Serial.print(".");
    }
}

bool wifiNotConnected(){
  return WiFi.status() != WL_CONNECTED;
}

void wifiConnectedStatus(){
  Serial.println("");
  Serial.println("Connected on Wifi");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
}