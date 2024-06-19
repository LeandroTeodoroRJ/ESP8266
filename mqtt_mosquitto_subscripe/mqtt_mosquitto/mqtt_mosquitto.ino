/*
 * Project name: MQTT Mosquito Subscripe
 * Description: Receving a message from Mosquitto MQTT topic
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 2.0
 * Last Uptate: 17.06.24
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
 *    2- To publish with Mosquitto MQTT command line:
 *      mosquitto_pub -t topic_name -h localhost -m "message"
 *      mosquitto_pub -t ESP8266/inTopic -h localhost -m "ON"
 *    3- To subscribe with Mosquitto MQTT command line:
 *      mosquitto_sub -t topic_name -h localhost
 *      mosquitto_sub -t ESP8266/inTopic -h localhost
 *
 */

#include "genericWIFI.h"
#include <PubSubClient.h>

#define RATE_115KBPS  115200
#define TIME_10_MS    10
#define MQTT_SERVER_IP "192.168.1.9"
#define SUBSCRIBE_TOPIC  "ESP8266/inTopic"
#define MQTT_PORT 1883
#define TIME_TO_RECONNECT_MS 5000
#define CLIENT_CONNECT_ERROR  1
#define TIME_TO_READ_MS 2000

const char* ssid = SSID_NAME;     
const char* password = PASSWORD;  

WiFiClient espClient;
PubSubClient client(espClient);

void connectServerMQTT();
void reconnect();
void showSerialMonitorMesure();
void messageConnectionFail();
void messageConnectionSuccessful();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  serialMonitorStart();
  WiFi.begin(ssid, password);
  WifiWatingConnect();  
  wifiConnectedStatus();
  connectServerMQTT();
}

void serialMonitorStart(){ 
    Serial.begin(RATE_115KBPS);
    delay(TIME_10_MS);
}

void connectServerMQTT(){
  client.setServer(MQTT_SERVER_IP, MQTT_PORT);
  reconnect();
  client.setCallback(callback);
  client.subscribe(SUBSCRIBE_TOPIC);
}

void loop() {  
  if (!client.connected()){
    reconnect();
  }
  client.loop();    
  delay(TIME_TO_READ_MS);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection..."); 

    try{
      if (!client.connect("ESP8266Client")){
        throw(CLIENT_CONNECT_ERROR);
      }
      else{
        client.subscribe(SUBSCRIBE_TOPIC);
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

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0; i<length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

