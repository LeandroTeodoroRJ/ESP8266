/*
 * Project name: Sensor Webserver
 * Description: Show on browser humidity and temperature from DHT11 sensor
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 23.03.24
 * Dependences: 
 *    Adafruit Unified Sensor 1.1.14
 *    DHT11 library - https://github.com/adafruit/DHT-sensor-library
 *    ESP8266WiFi
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
#include "DHT.h"

#define DHTPIN 5        // Output pin from DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "network_name";   //WiFi SSID name
const char* password = "password";      //WiFi password

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  server.begin();
  Serial.println("Start Webserver!");

  //IP Server
  Serial.print("Server IP:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Check if client is connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Waiting a new client
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  
  // Reading values from DHT11
  float u = dht.readHumidity(); 
  float t = dht.readTemperature(); 

  // Check there is reading error
  if (isnan(u) || isnan(t) ){
    Serial.println("DHT11 reading error!");
    return;
  }
  String txt = "";
    
  txt += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  txt += "<h3>Webserver with DHT11 Sensor.</h3>";
  txt += "<p>Humidity and Temperature</p>";
  
  client.print(txt);
  client.print(u);
  client.print(" %   ");
  client.print("<br>");
  client.print(t);
  client.print(" Celsius");
  client.print("</html>");
 
  delay(3000);
}

