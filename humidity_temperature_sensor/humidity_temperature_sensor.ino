/*
 * Project name: Humidity and Temperature Sensor
 * Description: Reading a DHT11 Sensor
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 2.0
 * Last Uptate: 09.06.24
 * Dependences: 
 *    Adafruit Unified Sensor 1.1.14
 *    DHT11 library - https://github.com/adafruit/DHT-sensor-library
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
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
#define RATE_115KBPS  115200
#define MESURE_DELAY_TIME 3000
#define BOTH_MESURE_ERROR 1

bool mesureIsNotValid(float humidity, float temperature);
void showReadErrorMessage();
void showMesures(float hum, float temp);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(RATE_115KBPS);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity(); 
  float temperature = dht.readTemperature(); 

  try{
    if (mesureIsNotValid(humidity, temperature)){
    throw(BOTH_MESURE_ERROR);
    return;
    }
  }
  catch(int code){
    showReadErrorMessage();
  }

  showMesures(humidity, temperature);
  delay(MESURE_DELAY_TIME);
}

bool mesureIsNotValid(float humidity, float temperature){
  return isnan(humidity) || isnan(temperature);
}

void showReadErrorMessage(){
  Serial.println("Falha na leitura!");
}

void showMesures(float hum, float temp){
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %\t");
  Serial.print("Tempeture: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.println(" ");
}

