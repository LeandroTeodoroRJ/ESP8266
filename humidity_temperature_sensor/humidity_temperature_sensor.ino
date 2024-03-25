/*
 * Project name: Humidity and Temperature Sensor
 * Description: Reading a DHT11 Sensor
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 21.03.24
 * Dependences: 
 *    Adafruit Unified Sensor 1.1.14
 *    DHT11 library - https://github.com/adafruit/DHT-sensor-library
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

#include "DHT.h"

#define DHTPIN 5        // Output pin from DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Serial start
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // Read humidity
  float u = dht.readHumidity(); 
  
  // Read temperature
  float t = dht.readTemperature(); 

  // Check that happen a read error
  if (isnan(u) || isnan(t) ){
    Serial.println("Falha na leitura!");
    return;
  }
  
  // Show results on serial port
  Serial.print("Humidity: ");
  Serial.print(u);
  Serial.println(" %\t");
  Serial.print("Tempeture: ");
  Serial.print(t);
  Serial.println(" Celsius");

  delay(3000);
}
