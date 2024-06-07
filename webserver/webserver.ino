/*
 * Project name: Web Server
 * Description: How to create a web server to show a simple HTML on browser after GET request.
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 17.03.24
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

const char* ssid = "SSID_name";  //SSID name
const char* password = "LAN_password";     //Password WiFi LAN

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected!");

  //Inicializar o servidor
  server.begin();
  Serial.println("Start Web Server!");

  //Apresenta o IP
  Serial.print("Server IP:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Wait to client connect
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait to response
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String txt = "";
  
  txt += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  txt += "<h1>Web Server!</h1>";
  txt += "</html>\n";
  client.print(txt);
  
  delay(1);
  Serial.println("");
}
