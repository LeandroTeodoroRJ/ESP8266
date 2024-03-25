/*
 * Project name: MQTT Mosquito Sensor
 * Description: Publishing the value read from analog input to mosquitto mqtt broker
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 25.03.24
 * Dependences:
 *    PubSubClient.h  --  by Nick O'Leary -- Ver 2.8.0
 *    ESP8266WiFi.h
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
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

#ifdef ESP8266
  #include <ESP8266WiFi.h>     /* WiFi library for ESP8266 */
#else
  #include <WiFi.h>            /* WiFi library for ESP32 */
#endif
#include <PubSubClient.h>

#define wifi_ssid "your SSID WiFi name"
#define wifi_password "Wifi password"
#define mqtt_server "192.168.1.9"

#define sensor_value_topic  "ESP8266/sensor/value"
int analog_value = 0;
#define ANALOG_PIN  A0

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
    
  if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
      
      delay(2000);  // Wait a few seconds between measurements.
      
      // Reading the sensor from analog pin
      analog_value = analogRead(ANALOG_PIN);

      Serial.print("Sensor Value: ");
      Serial.println(analog_value);

      //Publishing the sensor value to Mosquitto MQTT broker
      client.publish(sensor_value_topic, String(analog_value).c_str(), true);
}
