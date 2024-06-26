/*
 * Project name: Web Server
 * Description: How to create a web server to show a simple HTML on browser after GET request.
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
#define CLIENT_NOT_CONNECTED 0
#define HTTP_PORT 80
#define TIME_TO_REQUEST_MS 1

const char* ssid = SSID_NAME;     //wifi ssid name --string
const char* password = PASSWORD;  //wifi password --string

String html_template = "";  

WiFiServer server(HTTP_PORT);

void setup() {
  serialMonitorStart();
  WiFi.begin(ssid, password);
  WifiWatingConnect();
  startWebServer();
  showServerStatus();  
  makeHTMLTemplate();  
}

void serialMonitorStart(){ 
    Serial.begin(RATE_115KBPS);
    delay(TIME_10_MS);
}

void startWebServer(){
  server.begin();
  Serial.println("Start Web Server!");
}

void showServerStatus(){
  Serial.println("");
  Serial.println("Connected!");  
  Serial.print("Server IP:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void makeHTMLTemplate(){
  html_template += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  html_template += "<h1>Web Server!</h1>";
  html_template += "</html>\n";
}

void loop() {
  WiFiClient client = server.available();
  if (client == CLIENT_NOT_CONNECTED) {
    return;
  }
  else{
    Serial.println("New Client");
  }  
  waitingGetResquest(client); 
  responseTemplate(client);
}

void waitingGetResquest(WiFiClient client_request){
  while (!client_request.available()) {
    delay(TIME_TO_REQUEST_MS);
  }
}

void responseTemplate(WiFiClient client_request){
  client_request.print(html_template);  
  delay(TIME_TO_REQUEST_MS);
  Serial.println("");
}