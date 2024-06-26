/*
 * Project name: MQTT Mosquito Sensor
 * Description: Publishing the value read from analog input to mosquitto mqtt broker
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 2.2
 * Last Uptate: 15.06.24
 * Dependences:
 *    PubSubClient.h  --  by Nick O'Leary -- Ver 2.8.0
 *    ESP8266WiFi.h
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: 
 *    ModeMCU Ver3.0 - ESP8266
 *    ESP32
 *    Mosquitto local MQTT Broker
 *    MQTT Explorer (Optional)
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: 
 *    How to configure MQTT Mosquito broker LAN Port: https://fusion-automate.blogspot.com/2023/05/netsh-port-forwarding-from-lan.html
 * Other Notes: 
 *    1- Execute this command on windows to configure MQTT mosquito port
 *    netsh interface portproxy add v4tov4 listenport=[local port number] listenaddress=[local IP address] connectport=[local port number] connectaddress=[local IP address]
 *    Example: netsh interface portproxy add v4tov4 listenaddress=192.168.1.7 listenport=1883 connectaddress=127.0.0.1 connectport=1883
 *
 */

#include "genericWIFI.h"
#include <PubSubClient.h>
#include "genericAnalog.h"

#define RATE_115KBPS  115200
#define TIME_10_MS    10
#define MQTT_SERVER_IP "192.168.1.9"
#define SENSOR_VALUE_TOPIC  "ESP8266/sensor/value"
#define RETAINED_ACTIVE true
#define MQTT_PORT 1883
#define TIME_FOR_MESURE_MS  2000
#define TIME_TO_RECONNECT_MS 5000
#define CLIENT_CONNECT_ERROR  1

AnalogInput potentiometer(A0);
int analog_value = 0;

const char* ssid = SSID_NAME;     
const char* password = PASSWORD;  

WiFiClient espClient;
PubSubClient client(espClient);

void connectServerMQTT();
void reconnect();
void showSerialMonitorMesure();
void messageConnectionFail();
void messageConnectionSuccessful();

void setup() {
  serialMonitorStart();
  WiFi.begin(ssid, password);
  WifiWatingConnect();  
  wifiConnectedStatus();
  connectServerMQTT();
  potentiometer.setMaxValue(900);
}

void serialMonitorStart(){ 
    Serial.begin(RATE_115KBPS);
    delay(TIME_10_MS);
}

void connectServerMQTT(){
  client.setServer(MQTT_SERVER_IP, MQTT_PORT);
}

void loop() {  
  if (!client.connected()){
    reconnect();
  }
  client.loop();      
  analog_value = potentiometer.getValue();
  showSerialMonitorMesure();
  client.publish(SENSOR_VALUE_TOPIC, String(analog_value).c_str(), RETAINED_ACTIVE);
  delay(TIME_FOR_MESURE_MS);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection..."); 

    try{
      if (!client.connect("ESP8266Client")){
        throw(CLIENT_CONNECT_ERROR);
      }
      else{
        messageConnectionSuccessful();
      }       
    }
    catch(int code){
      messageConnectionFail();
      delay(TIME_TO_RECONNECT_MS);
    }
      
  }
}

void messageConnectionSuccessful(){
  Serial.println("connected");
}

void messageConnectionFail(){
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");  
}

void showSerialMonitorMesure(){
  Serial.print("Sensor Value: ");
  Serial.println(analog_value);
}

